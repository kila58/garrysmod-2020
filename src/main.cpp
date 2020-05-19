#include "garrysmod.hpp"

#include "features/lua/lua.hpp"

DWORD WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		lua.Init();
		return 1;
	}

	return 0;
}