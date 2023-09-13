#pragma once

#include "../hl2comm/hl2ss_network.h"
#include <winrt/Windows.Foundation.Numerics.h>

using namespace winrt::Windows::Foundation::Numerics;

struct PV_Struct {
	uint64_t timestamp;

	uint32_t valid;
};

typedef void(*PVSubscriptionCallback)(const PV_Struct* sample);

void Receive_PV_Initialize(HC_Context_Ptr& context, PVSubscriptionCallback cb, const char* topic);
void Receive_PV_Quit();
void Receive_PV_Cleanup();

