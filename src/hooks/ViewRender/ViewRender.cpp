#include "ViewRender.hpp"

#include "../src/garrysmod.hpp"

#include "../src/features/features.hpp"

using View_RenderType = void* (__thiscall*)(void*, vrect_t*);
View_RenderType original_function;

void __fastcall View_Render(void* instance, vrect_t* rect)
{
	original_function(instance, rect);

	BaseFeature::SetArguments(VIEWRENDER, instance, rect);
	features.Invoke(VIEWRENDER);
}

void ViewRenderHook::Init()
{
	hook = new Hook(client, 26, &View_Render);
	original_function = (View_RenderType)hook->ReplaceVirtual();
}

void ViewRenderHook::Destroy()
{
	hook->RevertVirtual();

	delete hook;
}

ViewRenderHook viewrender_hook;
