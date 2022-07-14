#pragma once

struct vrect_t
{
	int x, y, width, height;
	vrect_t *pnext;
};

class CBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		return GetVirtual<ClientClass* (__thiscall*)(void*)>(this, 8)(this);
	}
};