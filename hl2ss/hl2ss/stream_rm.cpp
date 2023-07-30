
#include "research_mode.h"
#include "server.h"
#include "stream_rm.h"
#include "stream_rm_vlc.h"
#include "stream_rm_imu.h"
#include "stream_rm_zab.h"
#include "log.h"
#include "ports.h"
#include "types.h"

#include "hl2ss_network.h"

#define FASTCDR_STATIC_LINK
#include "fastcdr/Cdr.h"

#include "pcpd_msgs/msg/Hololens2VideoStream.h"
#include "pcpd_msgs/msg/Hololens2Sensors.h"

#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Windows.Perception.Spatial.Preview.h>

using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::Perception::Spatial::Preview;

typedef void(*RM_MODE0)(IResearchModeSensor*, SOCKET);
typedef void(*RM_MODE1)(IResearchModeSensor*, SOCKET, SpatialLocator const&);
typedef void(*RM_MODE2)(IResearchModeSensor*, SOCKET);

struct RM_Context {
    std::string client_id;
    z_session_t session;
    RMStreamConfig config;
    bool valid{ false };
    bool first_frame_sent{ false };
};

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------


static HANDLE g_event_quit = NULL; // CloseHandle
static std::vector<HANDLE> g_threads; // CloseHandle

static RM_Context* g_zenoh_context = NULL;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------


// OK
static DWORD WINAPI RM_EntryPoint(void* param)
{
    SpatialLocator locator = nullptr;
    IResearchModeSensor* sensor;
    ResearchModeSensorType type;
    GUID nodeId;
    bool ok;

    sensor = (IResearchModeSensor*)param;
    type = sensor->GetSensorType();

    ShowMessage(L"RM%d (%s): Waiting for consent", type, sensor->GetFriendlyName());

    ok = ResearchMode_WaitForConsent(sensor);
    if (!ok) { 
        ShowMessage("Consent was rejected");
        return false; 
    }

    nodeId = ResearchMode_GetRigNodeId();
    locator = SpatialGraphInteropPreview::CreateLocatorForNode(nodeId);

    ShowMessage("RM%d: Start Stream", type);
    auto& ctx = *g_zenoh_context;

    bool enable_location = ctx.config.enable_location;
    switch (type)
    {
    case LEFT_FRONT:
    case LEFT_LEFT:
    case RIGHT_FRONT:
    case RIGHT_RIGHT:      
    {
        if (enable_location) {
            RM_VLC_Stream_Mode1(sensor, ctx.session, ctx.client_id.c_str(), ctx.config.vlc_format, locator);
        }
        else {
            RM_VLC_Stream_Mode0(sensor, ctx.session, ctx.client_id.c_str(), ctx.config.vlc_format);
        }
        break;
    }
    case DEPTH_AHAT:       
    {
        if (enable_location) {
            RM_ZHT_Stream_Mode1(sensor, ctx.session, ctx.client_id.c_str(), ctx.config.depth_format, locator);
        }
        else {
            RM_ZHT_Stream_Mode0(sensor, ctx.session, ctx.client_id.c_str(), ctx.config.depth_format);
        }
        break;
    }
    case DEPTH_LONG_THROW:
    {
        if (enable_location) {
            RM_ZLT_Stream_Mode1(sensor, ctx.session, ctx.client_id.c_str(), locator);
        }
        else {
            RM_ZLT_Stream_Mode0(sensor, ctx.session, ctx.client_id.c_str());
        }
        break;
    }
    case IMU_ACCEL:
    {
        if (enable_location) {
            RM_ACC_Stream_Mode1(sensor, ctx.session, ctx.client_id.c_str(), locator);
        }
        else {
            RM_ACC_Stream_Mode0(sensor, ctx.session, ctx.client_id.c_str());
        }
        break;
    }
    case IMU_GYRO:
    {
        if (enable_location) {
            RM_GYR_Stream_Mode1(sensor, ctx.session, ctx.client_id.c_str(), locator);
        }
        else {
            RM_GYR_Stream_Mode0(sensor, ctx.session, ctx.client_id.c_str());
        }
        break;
    }
    case IMU_MAG:
    {
        if (enable_location) {
            RM_MAG_Stream_Mode1(sensor, ctx.session, ctx.client_id.c_str(), locator);
        }
        else {
            RM_MAG_Stream_Mode0(sensor, ctx.session, ctx.client_id.c_str());
        }
        break;
    }
    }

    ShowMessage("RM%d: Stream Finished", type);
    //while (WaitForSingleObject(g_event_quit, 0) == WAIT_TIMEOUT);
  
    return 0;
}

// OK
void RM_Initialize(const char* client_id, z_session_t session, RMStreamConfig config)
{
    //ResearchModeSensorType const* sensortypes = ResearchMode_GetSensorTypes();
    int const sensorcount = ResearchMode_GetSensorTypeCount();

    if (sensorcount < 7) {
        // not on hololens2 ...
        config.enable_imu_accel = false;
        config.enable_imu_gyro = false;
        config.enable_imu_mag = false;
    }

    g_zenoh_context = new RM_Context(); // release
    g_zenoh_context->client_id = std::string(client_id);
    g_zenoh_context->session = session;
    g_zenoh_context->config = std::move(config);
    g_zenoh_context->valid = true;

    g_event_quit = CreateEvent(NULL, TRUE, FALSE, NULL);
    
    // check here if there might be a problem with the config (see readme about impossible combinations, like depth_ahat and depth_long_throw

    if (config.enable_left_front) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(LEFT_FRONT), NULL, NULL));
    }
    if (config.enable_left_left) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(LEFT_LEFT), NULL, NULL));
    }
    if (config.enable_right_front) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(RIGHT_FRONT), NULL, NULL));
    }
    if (config.enable_right_right) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(RIGHT_RIGHT), NULL, NULL));
    }
    if (config.enable_depth_ahat) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(DEPTH_AHAT), NULL, NULL));
    }
    if (config.enable_depth_long_throw) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(DEPTH_LONG_THROW), NULL, NULL));
    }
    if (config.enable_imu_accel) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(IMU_ACCEL), NULL, NULL));
    }
    if (config.enable_imu_gyro) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(IMU_GYRO), NULL, NULL));
    }
    if (config.enable_imu_mag) {
        g_threads.push_back(CreateThread(NULL, 0, RM_EntryPoint, ResearchMode_GetSensor(IMU_MAG), NULL, NULL));
    }

}

// OK
void RM_Quit()
{
    SetEvent(g_event_quit);
}

// OK
void RM_Cleanup()
{
    WaitForMultipleObjects((DWORD)g_threads.size(), g_threads.data(), TRUE, INFINITE);

    for (auto thread : g_threads) { CloseHandle(thread); }
    CloseHandle(g_event_quit);

    g_threads.clear();
    g_event_quit = NULL;

    free(g_zenoh_context);
    g_zenoh_context = NULL;
}
