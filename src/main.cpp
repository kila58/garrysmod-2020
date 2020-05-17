#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

DWORD WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{


		return 1;
	}

	return 0;
}