#include "lua.hpp"

bool Lua::Init()
{
	typedef void* (*CreateInterface_t)(const char* name, int* pReturnCode);
	CreateInterface_t CreateInterface = (CreateInterface_t)GetProcAddress(GetModuleHandle("lua_shared.dll"), "CreateInterface");

	luashared = (LuaShared*)CreateInterface("LUASHARED003", 0);
	if (!luashared)
		return false;

	auto client = luashared->GetLuaInterface(CLIENT);
	L = client->state;

	//LoadBuffer("print(1)");

	client->RunString("bruh", "bruh", "print(1)", true, true);

	return true;
}

lua_State* Lua::GetState()
{
	return L;
}

int Lua::LoadBuffer(std::string script, std::string name)
{
	auto str = script.c_str();
	return luaL_loadbuffer(L, str, strlen(str), name.c_str());
}

Lua lua;