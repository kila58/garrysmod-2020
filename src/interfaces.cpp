#include "interfaces.hpp"

#include "garrysmod.hpp"

bool Interfaces::Init()
{
	luashared = GetInterface<LuaShared*>("lua_shared.dll", "LUASHARED003");
	XASSERT(luashared);

	materialsystem = GetInterface<MaterialSystem*>("materialsystem.dll", "VMaterialSystem080");
	XASSERT(materialsystem);

	enginemodel = GetInterface<EngineModel*>("engine.dll", "VEngineModel016");
	XASSERT(enginemodel);

	cliententitylist = GetInterface<CClientEntityList*>("client.dll", "VClientEntityList003");
	XASSERT(cliententitylist);

	client = GetInterface<CBaseClientDLL*>("client.dll", "VClient017");
	XASSERT(client);

	steamclient = ((ISteamClient*(__cdecl*)(void))GetProcAddress(GetModuleHandle("steam_api64.dll"), "SteamClient"))();
	XASSERT(steamclient);

	HSteamUser steamuser = ((HSteamUser(__cdecl*)(void))GetProcAddress(GetModuleHandle("steam_api64.dll"), "SteamAPI_GetHSteamUser"))();
	HSteamPipe steampipe = ((HSteamPipe(__cdecl*)(void))GetProcAddress(GetModuleHandle("steam_api64.dll"), "SteamAPI_GetHSteamPipe"))();
	steamhttp = steamclient->GetISteamHTTP(steamuser, steampipe, "STEAMHTTP_INTERFACE_VERSION003");
	XASSERT(steamhttp);

	return true;
}

template<typename T>
T Interfaces::GetInterface(const char* module, const char* name)
{
	static tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(module), "CreateInterface");
	return (T)CreateInterface(name, 0);
}

Interfaces interfaces;