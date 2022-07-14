#include "garrysmod.hpp"

#include "interfaces.hpp"
#include "hooks/hooks.hpp"
#include "features/features.hpp"

#include "features/lua/lua.hpp"

DWORD WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		//bootstrap
		if (!interfaces.Init())
			return 0;

		lua.Init(); //needs to run before everything

		hooks.Init(); 

		features.Init();

		return 1;
	}

	return 0;
}