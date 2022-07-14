#pragma once

#include "../features.hpp"

#include "../src/garrysmod.hpp"

#include "entity.hpp"
#include "surface.hpp"
#include "render.hpp"
#include "menu.hpp"

class Lua
{
public:

	void Init();
	lua_State* GetState();
	int LoadBuffer(std::string script, std::string name = "");

private:
	lua_State* L;

	ILuaInterface* menu;
	ILuaInterface* client;
};

extern Lua lua;