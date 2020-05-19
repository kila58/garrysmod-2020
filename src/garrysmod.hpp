#pragma once

#include <Windows.h>
#include <string>
#include <cmath>

extern "C" {
#include "lua/src/lua.h"
#include "lua/src/lauxlib.h"
}

#include "color.hpp"
#include "angle.hpp"
#include "vector.hpp"

#include "sdk/ILuaInterface.hpp"

extern LuaShared* luashared;

