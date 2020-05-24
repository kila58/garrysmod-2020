#include "RunString.hpp"

void RunStringHook::Init()
{

}

void RunStringHook::Destroy()
{
	hook->RevertVirtual();

	delete hook;
}

RunStringHook runstring_hook;
