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

	clientinterface = GetInterface<CClientEntityList*>("client.dll", "VClient017");
	XASSERT(clientinterface);

	return true;
}

template<typename T>
T Interfaces::GetInterface(const char* module, const char* name)
{
	static tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(module), "CreateInterface");
	return (T)CreateInterface(name, 0);
}

Interfaces interfaces;