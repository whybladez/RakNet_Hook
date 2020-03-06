/*
	SA:MP ASI Framework
	Author: CentiuS
*/

#pragma once

#include <stdio.h> 
#include <stdint.h>
#include <assert.h>
#include <Windows.h>
#include <process.h>
#include <string>
#include <iostream>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "game/CVector.h"
#include "game/CPlayerInfo.h"
#include "game/CPed.h"
#include "game/CCamera.h"

#include "packet_handler.h"
#include "raknet/BitStream.h"
#include "raknet/RakClient.h"
#include "raknet/NetworkTypes.h"
#include "raknet/PacketEnumerations.h"
#include "raknet/PluginInterface.h"
#include "raknet/RakHook.h"

#include "samp.h"

extern SAMPFramework *pSAMP;