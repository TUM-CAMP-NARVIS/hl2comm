
#pragma once

#include "hl2ss_network.h"
#include <winrt/Windows.Perception.h>

void SI_Initialize(const char* client_id, z_session_t session);
void SI_Quit();
void SI_Cleanup();
