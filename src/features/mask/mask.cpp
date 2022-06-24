#include "mask.hpp"

using BeginRenderType = void* (__thiscall*)(void*); //fastcall?
BeginRenderType original_function;

void __fastcall BeginRender(void* instance)
{
	MessageBoxA(NULL, NULL, "2", NULL);
	original_function(instance);
}

bool Mask::Init()
{
	/*MatRenderContext* context = materialsystem->GetRenderContext();
	if (!context)
	{
		MessageBoxA(NULL, NULL, "1", NULL);
		return false;
	}

	hook = new Hook(context, 1, &BeginRender);
	original_function = (BeginRenderType)hook->ReplaceVirtual();*/

	return true;
}

Mask mask;	