
#include "research_mode.h"
#include "server.h"
#include "locator.h"
#include "timestamps.h"
#include "log.h"
#include <chrono>

#include "hl2ss_network.h"

#define FASTCDR_STATIC_LINK
#include "fastcdr/Cdr.h"

#include "pcpd_msgs/msg/Hololens2Sensors.h"


#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.Perception.h>
#include <winrt/Windows.Perception.Spatial.h>

using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception;
using namespace winrt::Windows::Perception::Spatial;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// Common *********************************************************************

// OK
template<class IResearchModeIMUFrame, class IMUDataStruct, bool ENABLE_LOCATION>
void RM_IMU_Stream(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, SpatialLocator const& locator, const bool& should_exit)
{

    std::string sub_path;
    pcpd_msgs::msg::Hololens2StreamDescriptor desc{};

    switch (sensor->GetSensorType()) {
    case IMU_ACCEL:
        sub_path = "imu_acc";
        desc.sensor_type(pcpd_msgs::msg::Hololens2SensorType::RM_IMU_ACCEL);
        break;
    case IMU_GYRO:
        sub_path = "imu_gyr";
        desc.sensor_type(pcpd_msgs::msg::Hololens2SensorType::RM_IMU_GYRO);
        break;
    case IMU_MAG:
        sub_path = "imu_mag";
        desc.sensor_type(pcpd_msgs::msg::Hololens2SensorType::RM_IMU_MAG);
        break;
    default:
        SPDLOG_INFO("RM_IMU: invalid config");
        return;

    }

    std::string keyexpr = std::string(topic_prefix) + "/str/" + sub_path;
    desc.stream_topic(keyexpr);
    desc.calib_topic(std::string(topic_prefix) + "/cfg/cal/" + sub_path);

    // publish streamdescriptor
    eprosima::fastcdr::FastBuffer buffer{};
    eprosima::fastcdr::Cdr buffer_cdr(buffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN, eprosima::fastcdr::Cdr::DDS_CDR);

    // put message to zenoh
    {
        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        desc.serialize(buffer_cdr);

        std::string keyexpr1 = std::string(topic_prefix) + "/cfg/desc/" + sub_path;
        z_put_options_t options1 = z_put_options_default();
        options1.encoding = z_encoding(Z_ENCODING_PREFIX_APP_CUSTOM, NULL);
        int res = z_put(session, z_keyexpr(keyexpr1.c_str()), (const uint8_t*)buffer.getBuffer(), buffer_cdr.getSerializedDataLength(), &options1);
        if (res > 0) {
            SPDLOG_INFO("RM_IMU: Error putting info");
        }
        else {
            SPDLOG_INFO("RM_IMU: put info: {}", keyexpr1);
        }
    }

    // publish calibration
    pcpd_msgs::msg::Hololens2RigidTransform calib{};
    {
        using namespace std::chrono;
        auto ts_ = nanoseconds(GetCurrentQPCTimestamp() * 100);
        auto ts_sec = static_cast<int32_t>(duration_cast<seconds>(ts_).count());
        auto ts_nsec = static_cast<int32_t>(duration_cast<nanoseconds>(ts_ - seconds(ts_sec)).count());

        calib.header().stamp().sec(ts_sec);
        calib.header().stamp().nanosec(ts_nsec);

        calib.header().frame_id(topic_prefix);
    }
    {
        DirectX::XMFLOAT4X4 e;
        ResearchMode_GetExtrinsics(sensor, e);
        DirectX::FXMMATRIX e1 = XMLoadFloat4x4(&e);;

        float4x4 extrinsics;
        XMStoreFloat4x4(&extrinsics, e1);

        // add flag to note it is enabled?
        float3 scale;
        quaternion rotation;
        float3 translation;

        if (decompose(extrinsics, &scale, &rotation, &translation)) {
            calib.position().x(translation.x);
            calib.position().y(translation.y);
            calib.position().z(translation.z);

            calib.orientation().x(rotation.x);
            calib.orientation().y(rotation.y);
            calib.orientation().z(rotation.z);
            calib.orientation().w(rotation.w);
        }
    }


    // put message to zenoh
    {
        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        calib.serialize(buffer_cdr);

        std::string keyexpr1 = std::string(topic_prefix) + "/cfg/cal/" + sub_path;
        z_put_options_t options1 = z_put_options_default();
        options1.encoding = z_encoding(Z_ENCODING_PREFIX_APP_CUSTOM, NULL);
        int res = z_put(session, z_keyexpr(keyexpr1.c_str()), (const uint8_t*)buffer.getBuffer(), buffer_cdr.getSerializedDataLength(), &options1);
        if (res > 0) {
            SPDLOG_INFO("RM_IMU: Error putting calib");
        }
        else {
            SPDLOG_INFO("RM_IMU: put calib: {}", keyexpr1);
        }
    }


    // should put another message for extrinsics (need idl for it)

    SPDLOG_INFO("PV: publish on: {0}", keyexpr.c_str());

    z_publisher_options_t publisher_options = z_publisher_options_default();
    publisher_options.priority = Z_PRIORITY_REAL_TIME;

    z_owned_publisher_t pub = z_declare_publisher(session, z_keyexpr(keyexpr.c_str()), &publisher_options);

    if (!z_check(pub)) {
        SPDLOG_INFO("RM_IMU: Error creating publisher");
        return;
    }

    z_publisher_put_options_t options = z_publisher_put_options_default();
    options.encoding = z_encoding(Z_ENCODING_PREFIX_APP_CUSTOM, NULL);


    PerceptionTimestamp ts = nullptr;
    float4x4 pose;
    IResearchModeSensorFrame* pSensorFrame; // Release
    ResearchModeSensorTimestamp timestamp;
    IResearchModeIMUFrame* pSensorIMUFrame; // Release    
    IMUDataStruct const* pIMUBuffer;
    size_t nIMUSamples;
    HRESULT hr;
    bool ok{ true };

    sensor->OpenStream();

    do
    {
    hr = sensor->GetNextBuffer(&pSensorFrame); // block
    if (FAILED(hr)) { break; }

    pSensorFrame->GetTimeStamp(&timestamp);
    pSensorFrame->QueryInterface(IID_PPV_ARGS(&pSensorIMUFrame));

    if constexpr(std::is_same_v<IResearchModeIMUFrame, IResearchModeAccelFrame>)
    {
        pSensorIMUFrame->GetCalibratedAccelarationSamples(&pIMUBuffer, &nIMUSamples);
        
        pcpd_msgs::msg::Hololens2ImuAccel value{};
        {
            using namespace std::chrono;
            auto ts_ = nanoseconds(timestamp.HostTicks * 100);
            auto ts_sec = static_cast<int32_t>(duration_cast<seconds>(ts_).count());
            auto ts_nsec = static_cast<int32_t>(duration_cast<nanoseconds>(ts_ - seconds(ts_sec)).count());

            value.header().stamp().sec(ts_sec);
            value.header().stamp().nanosec(ts_nsec);

            value.header().frame_id(topic_prefix);
        }
        value.vinyl_hup_ticks(pIMUBuffer->VinylHupTicks);
        value.soc_ticks(pIMUBuffer->SocTicks);
        auto& v = pIMUBuffer->AccelValues;
        value.values({v[0], v[1], v[2]});
        value.temperature(pIMUBuffer->temperature);

        if constexpr (ENABLE_LOCATION)
        {
            ts = QPCTimestampToPerceptionTimestamp(timestamp.HostTicks);
            pose = Locator_Locate(ts, locator, Locator_GetWorldCoordinateSystem(ts));

            float3 scale;
            quaternion rotation;
            float3 translation;

            if (decompose(pose, &scale, &rotation, &translation)) {
                value.position().x(translation.x);
                value.position().y(translation.y);
                value.position().z(translation.z);

                value.orientation().x(rotation.x);
                value.orientation().y(rotation.y);
                value.orientation().z(rotation.z);
                value.orientation().w(rotation.w);

            }
        }

        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        value.serialize(buffer_cdr);
    
    }
    else if constexpr(std::is_same_v<IResearchModeIMUFrame, IResearchModeGyroFrame>)
    {
        pSensorIMUFrame->GetCalibratedGyroSamples(&pIMUBuffer, &nIMUSamples);

        pcpd_msgs::msg::Hololens2ImuGyro value{};
        {
            using namespace std::chrono;
            auto ts_ = nanoseconds(timestamp.HostTicks * 100);
            auto ts_sec = static_cast<int32_t>(duration_cast<seconds>(ts_).count());
            auto ts_nsec = static_cast<int32_t>(duration_cast<nanoseconds>(ts_ - seconds(ts_sec)).count());

            value.header().stamp().sec(ts_sec);
            value.header().stamp().nanosec(ts_nsec);

            value.header().frame_id(topic_prefix);
        }
        value.vinyl_hup_ticks(pIMUBuffer->VinylHupTicks);
        value.soc_ticks(pIMUBuffer->SocTicks);
        auto& v = pIMUBuffer->GyroValues;
        value.values({ v[0], v[1], v[2] });
        value.temperature(pIMUBuffer->temperature);

        if constexpr (ENABLE_LOCATION)
        {
            ts = QPCTimestampToPerceptionTimestamp(timestamp.HostTicks);
            pose = Locator_Locate(ts, locator, Locator_GetWorldCoordinateSystem(ts));

            float3 scale;
            quaternion rotation;
            float3 translation;

            if (decompose(pose, &scale, &rotation, &translation)) {
                value.position().x(translation.x);
                value.position().y(translation.y);
                value.position().z(translation.z);

                value.orientation().x(rotation.x);
                value.orientation().y(rotation.y);
                value.orientation().z(rotation.z);
                value.orientation().w(rotation.w);

            }
        }

        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        value.serialize(buffer_cdr);

    }
    else if constexpr(std::is_same_v<IResearchModeIMUFrame, IResearchModeMagFrame>)
    {
        pSensorIMUFrame->GetMagnetometerSamples(&pIMUBuffer, &nIMUSamples);

        pcpd_msgs::msg::Hololens2ImuMag value{};
        {
            using namespace std::chrono;
            auto ts_ = nanoseconds(timestamp.HostTicks * 100);
            auto ts_sec = static_cast<int32_t>(duration_cast<seconds>(ts_).count());
            auto ts_nsec = static_cast<int32_t>(duration_cast<nanoseconds>(ts_ - seconds(ts_sec)).count());

            value.header().stamp().sec(ts_sec);
            value.header().stamp().nanosec(ts_nsec);

            value.header().frame_id(topic_prefix);
        }
        value.vinyl_hup_ticks(pIMUBuffer->VinylHupTicks);
        value.soc_ticks(pIMUBuffer->SocTicks);
        auto& v = pIMUBuffer->MagValues;
        value.values({ v[0], v[1], v[2] });

        if constexpr (ENABLE_LOCATION)
        {
            ts = QPCTimestampToPerceptionTimestamp(timestamp.HostTicks);
            pose = Locator_Locate(ts, locator, Locator_GetWorldCoordinateSystem(ts));

            float3 scale;
            quaternion rotation;
            float3 translation;

            if (decompose(pose, &scale, &rotation, &translation)) {
                value.position().x(translation.x);
                value.position().y(translation.y);
                value.position().z(translation.z);

                value.orientation().x(rotation.x);
                value.orientation().y(rotation.y);
                value.orientation().z(rotation.z);
                value.orientation().w(rotation.w);

            }
        }

        buffer_cdr.reset();
        buffer_cdr.serialize_encapsulation();
        value.serialize(buffer_cdr);
    }

    if (z_publisher_put(z_loan(pub), (const uint8_t*)buffer.getBuffer(), buffer_cdr.getSerializedDataLength(), &(options))) {
        SPDLOG_INFO("RM_IMU: Error publishing message");
        ok = false;
    }
    else {
        //SPDLOG_INFO("RM_IMU: published frame");
    }

    pSensorIMUFrame->Release();
    pSensorFrame->Release();
    }
    while (ok && !should_exit);

    sensor->CloseStream();
}

// ACC ************************************************************************

// OK
void RM_ACC_Stream_Mode0(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, const bool& should_exit)
{
    RM_IMU_Stream<IResearchModeAccelFrame, AccelDataStruct, false>(sensor, session, topic_prefix, nullptr, should_exit);
}

// OK
void RM_ACC_Stream_Mode1(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, SpatialLocator const& locator, const bool& should_exit)
{
    RM_IMU_Stream<IResearchModeAccelFrame, AccelDataStruct, true>(sensor, session, topic_prefix, locator, should_exit);
}


// GYR ************************************************************************

// OK
void RM_GYR_Stream_Mode0(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, const bool& should_exit)
{
    RM_IMU_Stream<IResearchModeGyroFrame, GyroDataStruct, false>(sensor, session, topic_prefix, nullptr, should_exit);
}

// OK
void RM_GYR_Stream_Mode1(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, SpatialLocator const& locator, const bool& should_exit)
{
    RM_IMU_Stream<IResearchModeGyroFrame, GyroDataStruct, true>(sensor, session, topic_prefix, locator, should_exit);
}


// MAG ************************************************************************

// OK
void RM_MAG_Stream_Mode0(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, const bool& should_exit)
{
    RM_IMU_Stream<IResearchModeMagFrame, MagDataStruct, false>(sensor, session, topic_prefix, nullptr, should_exit);
}

// OK
void RM_MAG_Stream_Mode1(IResearchModeSensor* sensor, z_session_t session, const char* topic_prefix, SpatialLocator const& locator, const bool& should_exit)
{
    RM_IMU_Stream<IResearchModeMagFrame, MagDataStruct, true>(sensor, session, topic_prefix, locator, should_exit);
}
