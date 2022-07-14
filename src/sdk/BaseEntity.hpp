#pragma once

class IClientEntity
{
public:
	ClientClass* GetClientClass()
	{
		return GetVirtual<ClientClass* (__thiscall*)(void*)>(this, 2)(this);
	}

	int GetIndex()
	{
		return GetVirtual<int (__thiscall*)(void*)>(this, 9)(this);
	}
};

class IClientRenderable
{
public:
	void DrawModel(int flag = 1)
	{
		return GetVirtual<void(__thiscall*)(void*, int)>(this, 10)(this, flag);
	}
};

class CBaseEntity
{
private:
	ptr GetOffset(const char* name)
	{
		return netvars.Get(name, GetClientEntity()->GetClientClass()->m_pRecvTable);
	}
	template <typename T>
	T GetNetVar(const char* name)
	{
		return *(T*)(this + GetOffset(name));
	}
	template <typename T>
	void SetNetVar(const char* name, const T& what)
	{
		*(T*)(this + GetOffset(name)) = what;
	}
	template <typename T>
	T Get(ptr offset)
	{
		return *(T*)(this + offset);
	}
	template <typename T>
	void Set(const T& what, ptr offset)
	{
		*(T*)(this + offset) = what;
	}

public:

	IClientEntity* GetClientEntity()
	{
		return GetVirtual<IClientEntity* (__thiscall*)(void*)>(this, 4)(this);
	}

	IClientRenderable* GetClientRenderable()
	{
		return GetVirtual<IClientRenderable* (__thiscall*)(void*)>(this, 5)(this);
	}

	__int64 GetCreationID() //serverside only??
	{
		return Get<__int64>(0x7F0);
	}

	int GetIndex()
	{
		return GetClientEntity()->GetIndex();
	}

	int GetHealth()
	{
		return GetNetVar<int>("m_iHealth");
	}

	VMatrix GetWorldTransformMatrix()
	{
		return Get<VMatrix>(GetOffset("m_CollisionGroup") - 0x4C);
	}

	Vector OBBMins()
	{
		return GetNetVar<Vector>("m_vecMins");
	}

	Vector OBBMaxs()
	{
		return GetNetVar<Vector>("m_vecMaxs");
	}

	bool IsPlayer(ILuaInterface* state)
	{
		if (!state)
			return false;

		return LuaBaseEntity::IsPlayer(state, GetIndex());
	}

	bool IsLocalPlayer(ILuaInterface* state)
	{
		if (!state)
			return false;

		//return (LuaBaseEntity::LocalPlayer(state) == this); //busted
		return false;
	}

	bool IsAlive(ILuaInterface* state)
	{
		if (!state)
			return false;

		return LuaBaseEntity::IsAlive(state, GetIndex());
	}

	bool IsDormant(ILuaInterface* state)
	{
		if (!state)
			return false;

		return LuaBaseEntity::IsDormant(state, GetIndex());
	}

	std::string GetName(ILuaInterface* state)
	{
		if (!state)
			return "unknown";

		return LuaBaseEntity::GetName(state, GetIndex());
	}

	Color GetTeamColor(ILuaInterface* state)
	{
		if (!state)
			return Color();

		return LuaBaseEntity::GetTeamColor(state, GetIndex());
	}

	void DrawModel(int flag = 1)
	{
		return GetClientRenderable()->DrawModel(flag);
	}
};