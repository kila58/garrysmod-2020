#include "hooks.hpp"

std::deque<BaseHook*> BaseHook::hooks;

void Hooks::Init()
{
	for (auto& hook : BaseHook::GetHooks())
		hook->Init();
}

void Hooks::Destroy()
{
	for (auto& hook : BaseHook::GetHooks())
		hook->Destroy();
}

Hooks hooks;