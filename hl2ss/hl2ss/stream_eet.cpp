
#include "server.h"
#include "locator.h"
#include "extended_eye_tracking.h"
#include "ports.h"
#include "timestamps.h"
#include "log.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.Perception.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Microsoft.MixedReality.EyeTracking.h>

#include "zenoh.h"

#define FASTCDR_STATIC_LINK
#include "fastcdr/Cdr.h"

#include "pcpd_msgs/msg/Hololens2EyeTracking.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Microsoft::MixedReality::EyeTracking;


struct EET_Context {
    std::string client_id;
    z_session_t session;
    uint8_t fps{ 0 };
    bool valid{ false };
};

struct EET_Frame
{
    float3   c_origin;
    float3   c_direction;
    float3   l_origin;
    float3   l_direction;
    float3   r_origin;
    float3   r_direction;
    float    l_openness;
    float    r_openness;
    float    vergence_distance;
    uint32_t valid;
};

struct EET_Packet
{
    uint64_t  timestamp;
    uint32_t  size;
    uint32_t  reserved;
    EET_Frame frame;
    float4x4  pose;
};

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

static HANDLE g_event_quit = NULL;
static HANDLE g_thread = NULL;
static EET_Context* g_zenoh_context = NULL;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// OK
static void EET_Stream(SpatialLocator const &locator, uint64_t utc_offset)
{

    if (g_zenoh_context == NULL || !g_zenoh_context->valid) {
        ShowMessage("EET: Error invalid context");
        return;
    }

    std::string keyexpr = "hl2/sensor/eet/" + g_zenoh_context->client_id;
    ShowMessage("EET: publish on: %s", keyexpr.c_str());

    z_owned_publisher_t pub = z_declare_publisher(g_zenoh_context->session, z_keyexpr(keyexpr.c_str()), NULL);

    if (!z_check(pub)) {
        ShowMessage("EET: Error creating publisher");
        return;
    }

    z_publisher_put_options_t options = z_publisher_put_options_default();
    options.encoding = z_encoding(Z_ENCODING_PREFIX_APP_CUSTOM, NULL);

    PerceptionTimestamp ts = nullptr;
    EyeGazeTrackerReading egtr = nullptr;
    DateTime td;
    EET_Packet eet_packet{};
    uint8_t fps = g_zenoh_context->fps;
    uint64_t delay;
    int64_t max_delta;
    int fps_index;
    bool cg_valid{ false };
    bool lg_valid{ false };
    bool rg_valid{ false };
    bool lo_valid{ false };
    bool ro_valid{ false };
    bool vd_valid{ false };
    bool ec_valid{ false };
    bool ok{ true };

    switch (fps)
    {
    case 30: fps_index = 0; break;
    case 60: fps_index = 1; break;
    case 90: fps_index = 2; break;
    default: 
        ShowMessage("EET: invalid fps");
        return;
    }

    max_delta = HNS_BASE / fps;
    delay = max_delta * 1;

    ExtendedEyeTracking_SetTargetFrameRate(fps_index);

    eprosima::fastcdr::FastBuffer buffer{};
    eprosima::fastcdr::Cdr buffer_cdr(buffer);

    do
    {

        eet_packet.timestamp = GetCurrentUTCTimestamp() - delay;

        Sleep(1000 / fps);
    
        egtr = ExtendedEyeTracking_GetReading(DateTime(QPCTimestampToTimeSpan(eet_packet.timestamp)), max_delta);
        bool got_data{ false };
        if (egtr)
        {
            eet_packet.timestamp = egtr.Timestamp().time_since_epoch().count() - utc_offset;

            cg_valid = egtr.TryGetCombinedEyeGazeInTrackerSpace(eet_packet.frame.c_origin, eet_packet.frame.c_direction);
            lg_valid = egtr.TryGetLeftEyeGazeInTrackerSpace(eet_packet.frame.l_origin, eet_packet.frame.l_direction);
            rg_valid = egtr.TryGetRightEyeGazeInTrackerSpace(eet_packet.frame.r_origin, eet_packet.frame.r_direction);
            lo_valid = egtr.TryGetLeftEyeOpenness(eet_packet.frame.l_openness);
            ro_valid = egtr.TryGetRightEyeOpenness(eet_packet.frame.r_openness);
            vd_valid = egtr.TryGetVergenceDistance(eet_packet.frame.vergence_distance);
            ec_valid = egtr.IsCalibrationValid();

            eet_packet.frame.valid = (vd_valid << 6) | (ro_valid << 5) | (lo_valid << 4) | (rg_valid << 3) | (lg_valid << 2) | (cg_valid << 1) | (ec_valid << 0);

            ts = QPCTimestampToPerceptionTimestamp(eet_packet.timestamp);
            eet_packet.pose = Locator_Locate(ts, locator, Locator_GetWorldCoordinateSystem(ts));
            got_data = true;
        }
        else
        {
            eet_packet.timestamp -= utc_offset;
            eet_packet.frame.valid = 0;
        }

        if (got_data) {

            // serialize to CDR
            pcpd_msgs::msg::Hololens2EyeTracking value{};

            value.timestamp(eet_packet.timestamp);

            {
                geometry_msgs::msg::Vector3 v_o{};
                v_o.x(eet_packet.frame.c_origin.x);
                v_o.y(eet_packet.frame.c_origin.y);
                v_o.z(eet_packet.frame.c_origin.z);
                value.c_origin(v_o);

                geometry_msgs::msg::Vector3 v_d{};
                v_d.x(eet_packet.frame.c_direction.x);
                v_d.y(eet_packet.frame.c_direction.y);
                v_d.z(eet_packet.frame.c_direction.z);
                value.c_direction(v_d);
            }

            {
                geometry_msgs::msg::Vector3 v_o{};
                v_o.x(eet_packet.frame.l_origin.x);
                v_o.y(eet_packet.frame.l_origin.y);
                v_o.z(eet_packet.frame.l_origin.z);
                value.l_origin(v_o);

                geometry_msgs::msg::Vector3 v_d{};
                v_d.x(eet_packet.frame.l_direction.x);
                v_d.y(eet_packet.frame.l_direction.y);
                v_d.z(eet_packet.frame.l_direction.z);
                value.l_direction(v_d);
            }

            {
                geometry_msgs::msg::Vector3 v_o{};
                v_o.x(eet_packet.frame.r_origin.x);
                v_o.y(eet_packet.frame.r_origin.y);
                v_o.z(eet_packet.frame.r_origin.z);
                value.r_origin(v_o);

                geometry_msgs::msg::Vector3 v_d{};
                v_d.x(eet_packet.frame.r_direction.x);
                v_d.y(eet_packet.frame.r_direction.y);
                v_d.z(eet_packet.frame.r_direction.z);
                value.r_direction(v_d);
            }

            value.l_openness(eet_packet.frame.l_openness);
            value.r_openness(eet_packet.frame.r_openness);
            value.valid(eet_packet.frame.valid);

            buffer_cdr.reset();
            value.serialize(buffer_cdr);

            // send message to zenoh
            if (z_publisher_put(z_loan(pub), (const uint8_t*)buffer.getBuffer(), buffer_cdr.getSerializedDataLength(), &options)) {
                ok = false;
                ShowMessage("EET: Error publishing message");
            }
            else {
                //ShowMessage("EET: published frame");
            }
        }
        else {
            //ShowMessage("EET: no data");
        }
    }
    while (ok && WaitForSingleObject(g_event_quit, 0) == WAIT_TIMEOUT);


    z_undeclare_publisher(z_move(pub));

}

// OK
static DWORD WINAPI EET_EntryPoint(void* param)
{
    (void)param;

    if (g_zenoh_context == NULL) {
        return 1;
    }

    SpatialLocator locator = nullptr;
    uint64_t utc_offset;
    
    ShowMessage("EET: Waiting for consent");

    ExtendedEyeTracking_Initialize();
    
    ExtendedEyeTracking_QueryCapabilities();

    locator = ExtendedEyeTracking_CreateLocator();
    utc_offset = GetQPCToUTCOffset(32);

    EET_Stream(locator, utc_offset);

    ShowMessage("EET: published done");

    return 0;
}

// OK
void EET_Initialize(const char* client_id, z_session_t session, uint8_t fps)
{
    g_zenoh_context = new EET_Context(); // release
    g_zenoh_context->client_id = std::string(client_id);
    g_zenoh_context->session = session;
    g_zenoh_context->fps = fps;
    g_zenoh_context->valid = true;

    g_event_quit = CreateEvent(NULL, TRUE, FALSE, NULL);
    g_thread = CreateThread(NULL, 0, EET_EntryPoint, NULL, 0, NULL);
}

// OK
void EET_Quit()
{
    SetEvent(g_event_quit);
}

// OK
void EET_Cleanup()
{
    WaitForSingleObject(g_thread, INFINITE);
    CloseHandle(g_thread);
    CloseHandle(g_event_quit);

    g_thread = NULL;
    g_event_quit = NULL;
    free(g_zenoh_context);
    g_zenoh_context = NULL;
}
