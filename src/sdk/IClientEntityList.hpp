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

	int NumberOfEntities(bool bIncludeNonNetworkable = false)
	{
		return GetVirtual<int(__thiscall*)(void*, bool)>(this, 5)(this, bIncludeNonNetworkable);
	}

	int GetHighestEntityIndex() //m_iMaxUsedServerIndex
	{
		return GetVirtual<int (__thiscall*)(void*)>(this, 6)(this) + 1;
	}

	int GetEntityCount()
	{
		return ents1 + ents2;
	}

private:
	char pad0[0x24];
	int ents1;
	char pad1[0xC];
	int ents2;
};