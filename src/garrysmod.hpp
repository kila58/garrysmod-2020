#pragma once

#include <Windows.h>
#include <string>
#include <cmath>

#define XASSERT( x ) if( !x ) MessageBoxW( 0, L#x, 0, 0 );

extern "C" {
#include "lua/src/lua.h"
#include "lua/src/lauxlib.h"
#include "lua/src/lualib.h"
#include "lua/src/lstate.h"
}

#include "definitions.hpp"
#include "color.hpp"
#include "angle.hpp"
#include "vector.hpp"
#include "hook.hpp"

template <typename T>
inline T GetVirtual(void* table, size_t index)
{
	return T((*(ptr**)table)[index]);
}

#include "sdk/ILuaInterface.hpp"
	#include "features/lua/player.hpp"
	#include "features/lua/surface.hpp"

#include "sdk/IMaterialSurface.hpp"
#include "sdk/BaseEntity.hpp"
#include "sdk/IClientEntityList.hpp"

extern LuaShared* luashared;
extern MaterialSystem* materialsystem;
extern EngineModel* enginemodel;
extern CClientEntityList* cliententitylist;
extern void* clientinterface; //?