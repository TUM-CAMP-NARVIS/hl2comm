
#pragma once

#include <stdint.h>
#include "configuration.h"
#include "zenoh.h"
#include "receive_eet.h"
#include "receive_pv.h"

#define UNITY_IMPORT extern "C" __declspec(dllimport)
typedef void(*ZenohSubscriptionCallBack)(const char* name, const z_sample_t& Sample);

UNITY_IMPORT
void InitializeStreamsOnUI(const char* cid, const char* zcfg, uint32_t enable);

UNITY_IMPORT
void DebugMessage(char const* str);

UNITY_IMPORT
bool RegisterRawZSubscriber(const char* name, const char* keyexpr, ZenohSubscriptionCallBack cb);

UNITY_IMPORT
bool ZSendMessage(const char* keyexpr, uint8_t * buffer, std::size_t buffer_len, z_encoding_prefix_t encoding, bool block);

UNITY_IMPORT
char* ZGet(const char* topic);

UNITY_IMPORT
int MQ_FreePayload(const char* data);

UNITY_IMPORT
void GetLocalIPv4Address(wchar_t* buffer, int size);

UNITY_IMPORT
int OverrideWorldCoordinateSystem(void* scs_ptr);

UNITY_IMPORT
bool StartEETReceiveOnUI(EETSubscriptionCallback cb, const char* topic);

UNITY_IMPORT
bool StopEETReceiveOnUI();

UNITY_IMPORT
bool StartPVReceiveOnUI(PVSubscriptionCallback cb, const char* topic);

UNITY_IMPORT
bool StopPVReceiveOnUI();
