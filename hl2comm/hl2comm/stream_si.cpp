
#include <queue>
#include "server.h"
#include "locator.h"
#include "spatial_input.h"
#include "ports.h"
#include "timestamps.h"
#include "log.h"
#include <chrono>

#include "hl2ss_network.h"

#define FASTCDR_STATIC_LINK
#include "fastcdr/Cdr.h"

#include "pcpd_msgs/msg/Hololens2HandTracking.h"
#include "pcpd_msgs/msg/Hololens2Sensors.h"

#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.Perception.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Windows.Perception.People.h>

using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::Perception::People;

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

static HANDLE g_thread = NULL; // CloseHandle
static HANDLE g_event_quit = NULL; // CloseHandle

static HC_Context_Ptr g_zenoh_context;
static bool g_first_frame_sent = false;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// OK
static void SI_Stream()
{

    if (!g_zenoh_context || !g_zenoh_context->valid) {
        SPDLOG_INFO("SI: Error invalid context");
        return;
    }
    std::string& topic_prefix = g_zenoh_context->topic_prefix;
    std::string keyexpr = topic_prefix + "/str/si";
    SPDLOG_INFO("SI: publish on: {0}", keyexpr.c_str());

    z_publisher_options_t publisher_options = z_publisher_options_default();
    publisher_options.priority = Z_PRIORITY_REAL_TIME;

    z_owned_publisher_t pub = z_declare_publisher(z_loan(g_zenoh_context->session), z_keyexpr(keyexpr.c_str()), &publisher_options);

    if (!z_check(pub)) {
        SPDLOG_INFO("SI: Error creating publisher");
        return;
    }
    Sleep(1);

    z_publisher_put_options_t options = z_publisher_put_options_default();
    options.encoding = z_encoding(Z_ENCODING_PREFIX_APP_CUSTOM, NULL);

    eprosima::fastcdr::FastBuffer buffer{};
    eprosima::fastcdr::Cdr buffer_cdr(buffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

    {
        pcpd_msgs::msg::Hololens2StreamDescriptor value{};

        value.stream_topic(g_zenoh_context->topic_prefix + "/str/si");
        value.calib_topic("");
        value.sensor_type(pcpd_msgs::msg::Hololens2SensorType::HAND_TRACKING);
        value.frame_rate(30);

        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        value.serialize(buffer_cdr);

        // put message to zenoh
        std::string keyexpr1 = g_zenoh_context->topic_prefix + "/cfg/desc/si";
        z_put_options_t options1 = z_put_options_default();
        options1.encoding = z_encoding(Z_ENCODING_PREFIX_APP_CUSTOM, NULL);
        int res = z_put(z_loan(g_zenoh_context->session), z_keyexpr(keyexpr1.c_str()), (const uint8_t*)buffer.getBuffer(), buffer_cdr.getSerializedDataLength(), &options1);
        if (res > 0) {
            SPDLOG_INFO("SI: Error putting info");
        }
        else {
            SPDLOG_INFO("SI: put info: {}", keyexpr1);
        }
    }

    PerceptionTimestamp ts = nullptr;
    SpatialCoordinateSystem world = nullptr;
    UINT64 qpc;
    int status1;
    int status2;
    uint8_t valid;
    std::vector<JointPose> left_poses;
    std::vector<JointPose> right_poses;
    SpatialInput_Frame head_pose;
    SpatialInput_Ray eye_ray;
    bool ok{ true };
    
    left_poses.resize(HAND_JOINTS);
    right_poses.resize(HAND_JOINTS);

    do
    {
        Sleep(1000 / 30);
        
        pcpd_msgs::msg::Hololens2HandTracking value{};

        qpc = GetCurrentQPCTimestamp();
        ts = QPCTimestampToPerceptionTimestamp(qpc);

        {
            using namespace std::chrono;
            auto ts_ = nanoseconds(qpc * 100);
            auto ts_sec = static_cast<int32_t>(duration_cast<seconds>(ts_).count());
            auto ts_nsec = static_cast<int32_t>(duration_cast<nanoseconds>(ts_ - seconds(ts_sec)).count());

            value.header().stamp().sec(ts_sec);
            value.header().stamp().nanosec(ts_nsec);

            value.header().frame_id(topic_prefix);
        }


        world   = Locator_GetWorldCoordinateSystem(ts);
        status1 = SpatialInput_GetHeadPoseAndEyeRay(world, ts, head_pose, eye_ray);
        status2 = SpatialInput_GetHandPose(world, ts, left_poses, right_poses);
        valid   = (status1 | (status2 << 2)) & 0x0F;

        {
            geometry_msgs::msg::Vector3 h_p{};
            h_p.x(head_pose.position.x);
            h_p.y(head_pose.position.y);
            h_p.z(head_pose.position.z);
            value.head_position(h_p);

            geometry_msgs::msg::Vector3 h_f{};
            h_f.x(head_pose.forward.x);
            h_f.y(head_pose.forward.y);
            h_f.z(head_pose.forward.z);
            value.head_forward(h_f);

            geometry_msgs::msg::Vector3 h_u{};
            h_u.x(head_pose.up.x);
            h_u.y(head_pose.up.y);
            h_u.z(head_pose.up.z);
            value.head_up(h_u);
        }
        {
            geometry_msgs::msg::Vector3 g_o{};
            g_o.x(eye_ray.origin.x);
            g_o.y(eye_ray.origin.y);
            g_o.z(eye_ray.origin.z);
            value.gaze_origin(g_o);

            geometry_msgs::msg::Vector3 g_d{};
            g_d.x(eye_ray.direction.x);
            g_d.y(eye_ray.direction.y);
            g_d.z(eye_ray.direction.z);
            value.gaze_direction(g_d);
        }

        std::vector < pcpd_msgs::msg::Hololens2HandJointPose> lps(left_poses.size());
        std::vector < pcpd_msgs::msg::Hololens2HandJointPose> rps(right_poses.size());

        for (unsigned i = 0; i < left_poses.size(); ++i) {
            auto& s = left_poses.at(i);
            auto& t = lps.at(i);
            switch (s.Accuracy) {
            case winrt::Windows::Perception::People::JointPoseAccuracy::Approximate:
                t.accuracy(pcpd_msgs::msg::Hololens2JointPoseAccuracy::Approximate);
                break;
            case winrt::Windows::Perception::People::JointPoseAccuracy::High:
                t.accuracy(pcpd_msgs::msg::Hololens2JointPoseAccuracy::High);
                break;
            }
            t.radius(s.Radius);

            t.position().x(s.Position.x);
            t.position().y(s.Position.y);
            t.position().z(s.Position.z);

            t.orientation().x(s.Orientation.x);
            t.orientation().y(s.Orientation.y);
            t.orientation().z(s.Orientation.z);
            t.orientation().w(s.Orientation.w);

        }
        value.right_poses(rps);
        value.left_poses(lps);
        value.valid(valid);

        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        value.serialize(buffer_cdr);

        // send message to zenoh
        if (z_publisher_put(z_loan(pub), (const uint8_t*)buffer.getBuffer(), buffer_cdr.getSerializedDataLength(), &options)) {
            ok = false;
            SPDLOG_INFO("SI: Error publishing message");
        }
        else {
            //SPDLOG_INFO("SI: published frame");
        }
    }
    while (ok && WaitForSingleObject(g_event_quit, 0) == WAIT_TIMEOUT && !g_zenoh_context->should_exit);
}

// OK
static DWORD WINAPI SI_EntryPoint(void *param)
{
    (void)param;

    if (!g_zenoh_context) {
        return 1;
    }

    SPDLOG_INFO("SI: Waiting for consent");

    SpatialInput_WaitForEyeConsent();

    SI_Stream();

    SPDLOG_INFO("SI: publisher done");

    return 0;
}

// OK
void SI_Initialize(HC_Context_Ptr& context)
{

    g_first_frame_sent = false;
    g_zenoh_context = context;

    g_event_quit = CreateEvent(NULL, TRUE, FALSE, NULL);
    g_thread = CreateThread(NULL, 0, SI_EntryPoint, NULL, 0, NULL);
}

// OK
void SI_Quit()
{
    SetEvent(g_event_quit);
}

// OK
void SI_Cleanup()
{
    WaitForSingleObject(g_thread, INFINITE);
    CloseHandle(g_thread);
    CloseHandle(g_event_quit);

    g_zenoh_context.reset();
    g_first_frame_sent = false;}
