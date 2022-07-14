#pragma once

//windows
#include <Windows.h>
#include <Psapi.h>
#include <winternl.h>

//std
#include <string>
#include <cmath>
#include <set>
#include <algorithm>
#include <random>

#define XASSERT( x ) if( !x ) MessageBoxW( 0, L#x, 0, 0 );

extern "C" {
#include "lua/src/lua.h"
#include "lua/src/lauxlib.h"
#include "lua/src/lualib.h"
#include "lua/src/lstate.h"
}

#include "detours/include/detours.h"

#include "definitions.hpp"
#include "color.hpp"
#include "angle.hpp"
#include "vector.hpp"
#include "netvar.hpp"
#include "memory.hpp"
#include "hook.hpp"

template <typename T>
inline T GetVirtual(void* table, size_t index)
{
	return T((*(ptr**)table)[index]);
}

#include "sdk/ILuaInterface.hpp"
	#include "features/lua/entity.hpp"
	#include "features/lua/surface.hpp"
	#include "features/lua/render.hpp"
	#include "features/lua/menu.hpp"

#include "sdk/IMaterialSurface.hpp"
#include "sdk/BaseEntity.hpp"
#include "sdk/IBaseClientDLL.hpp"
#include "sdk/ISteamCLient.hpp"
#include "sdk/IClientEntityList.hpp"

extern LuaShared* luashared;
extern MaterialSystem* materialsystem;
extern EngineModel* enginemodel;
extern CBaseClientDLL* client;
extern ISteamClient* steamclient;
extern void* steamhttp;
extern CClientEntityList* cliententitylist;