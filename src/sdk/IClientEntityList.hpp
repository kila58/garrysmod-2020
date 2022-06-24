#pragma once

class CClientEntityList
{
public:
	CBaseEntity* GetClientEntity(int index)
	{
		return GetVirtual<CBaseEntity* (__thiscall*)(void*, int)>(this, 3)(this, index);
	}

	CBaseEntity* GetClientEntityFromHandle(int handle)
	{
		return GetVirtual<CBaseEntity* (__thiscall*)(void*, int)>(this, 4)(this, handle);
	}

	int GetHighestEntityIndex()
	{
		return GetVirtual<int (__thiscall*)(void*)>(this, 4)(this);
	}
};