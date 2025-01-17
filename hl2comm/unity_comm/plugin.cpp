﻿
#include <mfapi.h>
#include <thread>
#include <future>
#include <tuple>
#include <utility>
#include "configuration.h"
#include "ipc.h"
#include "plugin.h"

#ifdef UNITY_WIN
#include <Windows.h>
#endif

#include "../hl2comm/log.h"

#include <chrono>

#include "../hl2comm/hl2ss_network.h"
#include "../hl2comm/manager.h"

#define FASTCDR_STATIC_LINK
#include "fastcdr/Cdr.h"

#include "receive_eet.h"
#include "receive_pv.h"



// --------------------------------------------------------------------------
// Helper for Deferred Call

template<typename Func, typename... Args>
auto call_deferred(Func&& func, Args &&... args) {
    // capture our task into lambda with all its parameters
    auto capture = [func = std::forward<Func>(func),
        args = std::make_tuple(std::forward<Args>(args)...)]()
        mutable {
        return std::apply(std::move(func), std::move(args));
    };

    HANDLE event_done = CreateEvent(NULL, TRUE, FALSE, NULL);
    std::future<bool> result = std::async(std::launch::async, [&capture, &event_done]() -> bool {
        capture();
        SetEvent(event_done);
        return true;
        });
    
    WaitForSingleObject(event_done, INFINITE);
    CloseHandle(event_done);
    return result.get();
}


// --------------------------------------------------------------------------
// UnitySetInterfaces

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;

static HC_Context_Ptr g_zenoh_context;

extern "C" void	UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
    s_UnityInterfaces = unityInterfaces;
    s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
    s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

#if SUPPORT_VULKAN
    if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
    {
        extern void NativeBufferAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
        NativeBufferAPI_Vulkan_OnPluginLoad(unityInterfaces);
    }
#endif // SUPPORT_VULKAN

    // Run OnGraphicsDeviceEvent(initialize) manually on plugin load
    OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
    if (s_Graphics) {
        s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
    }

    if (g_zenoh_context != nullptr) {
        MQ_Quit();
        MQ_Cleanup();
        StopManager(g_zenoh_context);
        g_zenoh_context.reset();
    }

}

// --------------------------------------------------------------------------
// GraphicsDeviceEvent


//static NativeBufferAPI* s_CurrentAPI = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;


static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
    // Create graphics API implementation upon initialization
    if (eventType == kUnityGfxDeviceEventInitialize)
    {
        //assert(s_CurrentAPI == NULL);
        s_DeviceType = s_Graphics->GetRenderer();
        //s_CurrentAPI = CreateNativeBufferAPI(s_DeviceType);
    }

    // Let the implementation process the device related events
    //if (s_CurrentAPI)
    //{
    //    s_CurrentAPI->ProcessDeviceEvent(eventType, s_UnityInterfaces);
    //}

    // Cleanup graphics API implementation upon shutdown
    if (eventType == kUnityGfxDeviceEventShutdown)
    {
        //delete s_CurrentAPI;
        //s_CurrentAPI = NULL;
        s_DeviceType = kUnityGfxRendererNull;
    }
}



// --------------------------------------------------------------------------
// OnRenderEvent
// This will be called for GL.IssuePluginEvent script calls; eventID will
// be the integer passed to IssuePluginEvent. In this example, we just ignore
// that value.

static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
    // Unknown / unsupported graphics device type? Do nothing
    //if (s_CurrentAPI == NULL)
    //    return;
    //s_CurrentAPI->OnRenderEvent(eventID);
}




//-----------------------------------------------------------------------------
// HL2Comm Interface
//-----------------------------------------------------------------------------

// from https://stackoverflow.com/questions/43732825/use-debug-log-from-c

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API 
RegisterLoggingCallback(LoggingFuncCallBack cb) {
    SetupCallbackLogSink(cb);
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
RegisterRawZSubscriber(const char* name, const char* keyexpr, ZenohSubscriptionCallBack cb) {
    return MQ_SetupZenohRawSubscription(name, keyexpr, cb);
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
ZSendMessage(const char* keyexpr, uint8_t * buffer, std::size_t buffer_len, z_encoding_prefix_t encoding, bool block) {
    return MQ_SendMessage(keyexpr, buffer, buffer_len, encoding, block);
}

typedef char* charptr;

extern "C" charptr UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
ZGet(const char* topic) {
    char* result = nullptr;
    if (!g_zenoh_context) {
        SPDLOG_ERROR("SetupZenohRawSubscription called, but Zenoh context is empty.");
        return result;
    }

    z_keyexpr_t keyexpr = z_keyexpr(topic);
    if (!z_check(keyexpr)) {
        SPDLOG_ERROR("{0} is not a valid key expression", topic);
        return result;
    }

    z_owned_reply_channel_t channel = zc_reply_fifo_new(16);
    z_get_options_t opts = z_get_options_default();
    z_get(z_loan(g_zenoh_context->session), keyexpr, "", z_move(channel.send),
        &opts);  // here, the send is moved and will be dropped by zenoh when adequate
    z_owned_reply_t reply = z_reply_null();

    SPDLOG_DEBUG("ZGet: get from topic: {0}", topic);
    for (z_call(channel.recv, &reply); z_check(reply); z_call(channel.recv, &reply)) {
        if (z_reply_is_ok(&reply)) {
            z_sample_t sample = z_reply_ok(&reply);

            result = new char[sample.payload.len];

            z_owned_str_t keystr = z_keyexpr_to_string(sample.keyexpr);
            SPDLOG_DEBUG("ZGet Received ('{0}' len: {1})", z_loan(keystr), (int)sample.payload.len);
            memcpy(result, sample.payload.start, sample.payload.len);

            z_drop(z_move(keystr));
        }
        else {
            SPDLOG_ERROR("ZGet: Received an error");
        }
    }
    z_drop(z_move(reply));
    z_drop(z_move(channel));

    return result;
}

extern "C" int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
MQ_FreePayload(const char* data) {
    delete[] data;
    return 0;
}


// OK
void InitializeStreams(const char* _topic_prefix, const char* zcfg, uint32_t enable=0x00000000)
{
    if (g_zenoh_context != nullptr) {
        // plugin is already initialized
        // we could check the diff between the enabled streams and adapt for it ??
        return;
    }

    if (enable) {
        SPDLOG_WARN("The currently loaded version of the plugin does not support HL2 streams.");
    }

    // testing zenoh in uwp app
    z_owned_config_t config = z_config_default();
    if (strlen(zcfg) > 0) {
        // configure from zcfg
        config = zc_config_from_str(zcfg);
    }
    if (!z_check(config)) {
        // error
        return;
    }

    g_zenoh_context = std::make_shared<HC_Context>();

    /*
     * Topic prefix consists of the following components
     * - namespace: tcn (Tum Camp Narvis)
     * - site: loc (default for unrouted networks)
     * - category: [hl2|svc|srg|...] The category of the entry
     * - entity_id: the entity id, unique to the namespace/site parent
     *   (to avoid issues it is better to have globally unique ids.)
     * - comm_type: [str|cfg|rpc] either streaming, configuration or remote-procedure calls
     *
     */
    std::string default_topic_prefix{"tcn/loc/dev/"};

    std::string topic_prefix(_topic_prefix);
    if (topic_prefix.empty()) {
        std::string host_name{"device00"};
#ifdef UNITY_WIN
        char buffer[256];
        if (gethostname(buffer, sizeof(buffer) == 0)) {
            host_name = std::string(buffer);
        }
        else {
            SPDLOG_ERROR("Cannot get Hostname - use device00 as default.");
        }
#endif
        topic_prefix = default_topic_prefix + host_name;
    }

    g_zenoh_context->topic_prefix = topic_prefix;
    SPDLOG_INFO("Using Topic Prefix: {0}", g_zenoh_context->topic_prefix);

    g_zenoh_context->session = z_open(z_move(config));
    if (!z_check(g_zenoh_context->session)) {
        // error
        return;
    }

    g_zenoh_context->streams_enabled = enable;
    g_zenoh_context->streams_started = 0x00;
    g_zenoh_context->valid = true;


    auto logger = std::make_shared<spdlog::logger>("hl2comm");
    logger->set_level(spdlog::level::debug);
    logger->set_pattern("%H:%M:%S.%e [%L] %v (%@, %t)");
    spdlog::set_default_logger(logger);

    spdlog::flush_every(std::chrono::milliseconds(500));
    spdlog::flush_on(spdlog::level::debug);

    SetupDebugLogSink();
    SPDLOG_INFO("Init logging");

    StartManager(g_zenoh_context);

    MQ_Initialize(g_zenoh_context);


}

void TeardownStreams() {
    if (g_zenoh_context != nullptr) {
        MQ_Quit();
        MQ_Cleanup();
        StopManager(g_zenoh_context);
        g_zenoh_context.reset();
    }
}

// OK
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
InitializeStreamsOnUI(const char* topic_prefix, const char* zcfg, uint32_t enable)
{
    call_deferred(InitializeStreams, topic_prefix, zcfg, enable);
}



// OK
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
TeardownStreamsOnUI()
{
    call_deferred(TeardownStreams);
}

// OK
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
DebugMessage(char const* str)
{
    SPDLOG_INFO("{0}", str);
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
StartEETReceiveOnUI(EETSubscriptionCallback cb, const char* topic)
{
    if (!g_zenoh_context) { return false; }
    call_deferred(Receive_EET_Initialize, g_zenoh_context, cb, topic);
    return true;
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
StopEETReceiveOnUI()
{
    if (!g_zenoh_context) { return false; }
    call_deferred(Receive_EET_Quit);
    call_deferred(Receive_EET_Cleanup);
    return true;
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
StartPVReceiveOnUI(PVSubscriptionCallback cb, const char* topic)
{
    if (!g_zenoh_context) { return false; }
    call_deferred(Receive_PV_Initialize, g_zenoh_context, cb, topic);
    return true;
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
StopPVReceiveOnUI()
{
    if (!g_zenoh_context) { return false; }
    call_deferred(Receive_PV_Quit);
    call_deferred(Receive_PV_Cleanup);
    return true;
}