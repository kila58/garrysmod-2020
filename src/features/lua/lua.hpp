#pragma once

#include "../src/garrysmod.hpp"

#include "surface.hpp"
#include "render.hpp"
#include "player.hpp"

class Lua
{
public:
	bool Init();
	lua_State* GetState();
	int LoadBuffer(std::string script, std::string name = "");

private:
	lua_State* L;
};

extern Lua lua;