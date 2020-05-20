#include "lua.hpp"

bool Lua::Init()
{
	typedef void* (*CreateInterface_t)(const char* name, int* pReturnCode);
	CreateInterface_t CreateInterface = (CreateInterface_t)GetProcAddress(GetModuleHandle("lua_shared.dll"), "CreateInterface");

	int bruh = 0;
	luashared = (LuaShared*)CreateInterface("LUASHARED003", &bruh);
	if (!luashared)
		return false;

	auto client = luashared->GetLuaInterface(MENU);
	if (!client)
		return false;

	MessageBoxA(NULL, std::to_string((DWORD64)client).c_str(), NULL, NULL);

	lua_State* state = client->GetState();
	if (!state)
		return false;

	//state->l_G->mainthread = state;

	L = state;

	LoadBuffer("print(1)");
	lua_pcall(L, 0, 0, 0);

	//client->RunString("bruh", "bruh", "print(1)", true, true);

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