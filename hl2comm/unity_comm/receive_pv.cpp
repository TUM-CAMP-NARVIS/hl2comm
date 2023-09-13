#include "../hl2comm/server.h"
#include "../hl2comm/locator.h"
#include "../hl2comm/ports.h"
#include "../hl2comm/timestamps.h"
#include "../hl2comm/log.h"
#include <chrono>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.Perception.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Microsoft.MixedReality.EyeTracking.h>

#include "../hl2comm/hl2ss_network.h"

#include "pcpd_msgs/msg/Hololens2VideoStream.h"
#include "pcpd_msgs/msg/Hololens2Sensors.h"

#include "zenoh.h"

#include "receive_PV.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Microsoft::MixedReality::EyeTracking;



struct subscriber_context;

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

static HANDLE g_event_quit = NULL;

static HC_Context_Ptr g_zenoh_context;

static subscriber_context* g_pv_subs_ctx = NULL;

static z_owned_subscriber_t g_pv_sub;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

struct subscriber_context {
    const char* name{ nullptr };
    PVSubscriptionCallback callback;

    void init_context() {}

    void data_handler(const z_sample_t* sample) {
        using namespace std::chrono;
        spdlog::info("PV: received sample: payload len:{0}", sample->payload.len);

        z_owned_str_t keystr = z_keyexpr_to_string(sample->keyexpr);

        char* buffer_start = const_cast<char*>(reinterpret_cast<const char*>(sample->payload.start)); // not sure why we need to const_cast here .. we won't modify the buffer ..
        eprosima::fastcdr::FastBuffer cdrbuffer(buffer_start, sample->payload.len);
        eprosima::fastcdr::Cdr cdr_des(cdrbuffer);
        cdr_des.read_encapsulation();
        spdlog::info("PV: received sample 01");

        pcpd_msgs::msg::Hololens2VideoStream msg{};
        cdr_des >> msg;
        spdlog::info("PV: received sample 02");

        PV_Struct PV_struct;

        PV_struct.timestamp = duration_cast<nanoseconds>(seconds(msg.header().stamp().sec()) + nanoseconds(msg.header().stamp().nanosec())).count();
        PV_struct.valid = true;


        spdlog::info("callback with PV_sample");
        callback(&PV_struct);

        z_drop(z_move(keystr));
    }

    void teardown_context() {}
};


void PV_handle_subscriber_callback(const z_sample_t* sample, void* context) {
    auto handle = static_cast<subscriber_context*>(context);
    if (handle != nullptr && sample != nullptr) {
        try {
            handle->data_handler(sample);
        }
        catch (const std::exception& e) {
            SPDLOG_ERROR("Error during subscription callback for: {0} -> {1}", handle->name, e.what());
        }
    }
    else {
        SPDLOG_ERROR("Invalid handle or sample during subscription callback.");
    }
}

void PV_free_subscriber_context(void* context) {
    if (context != nullptr) {
        free(context);
    }
}


// OK
void Receive_PV_Initialize(HC_Context_Ptr& context, PVSubscriptionCallback cb, const char* topic)
{
    g_zenoh_context = context;

    g_event_quit = CreateEvent(NULL, TRUE, FALSE, NULL);
    g_pv_subs_ctx = new subscriber_context();
    g_pv_subs_ctx->name = "pv_subscriber";
    g_pv_subs_ctx->callback = cb;

    // zclosure macro does not work with c++17
    z_owned_closure_sample_t callback{};
    callback.call = &PV_handle_subscriber_callback;
    callback.context = g_pv_subs_ctx;
    callback.drop = PV_free_subscriber_context;

    auto options = z_subscriber_options_default();

    g_pv_subs_ctx->init_context();

    //std::string expr = g_zenoh_context->topic_prefix + "/cfg/desc/PV";
    //printf("Declaring Subscriber on '%s'...\n", expr);
    g_pv_sub = z_declare_subscriber(z_loan(g_zenoh_context->session), z_keyexpr(topic), z_move(callback), &options);
    if (!z_check(g_pv_sub)) {
        spdlog::error("Unable to declare subscriber.");
        return;
    }
}

// OK
void Receive_PV_Quit()
{
    SetEvent(g_event_quit);
}

// OK
void Receive_PV_Cleanup()
{
    CloseHandle(g_event_quit);

    g_event_quit = NULL;

    z_undeclare_subscriber(z_move(g_pv_sub));

    if (g_pv_subs_ctx != NULL) {
        g_pv_subs_ctx->teardown_context();
    }

    g_zenoh_context.reset();
}