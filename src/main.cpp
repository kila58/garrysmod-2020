#include "garrysmod.hpp"

#include "interfaces.hpp"
#include "hooks/hooks.hpp"

#include "features/lua/lua.hpp"
#include "features/mask/mask.hpp"
#include "features/playeresp/playeresp.hpp"

DWORD WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		//bootstrap
		interfaces.Init();
		hooks.Init(); 

		//features
		lua.Init();
		mask.Init();
		playeresp.Init();

		return 1;
	}

	return 0;
}