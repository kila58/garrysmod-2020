#pragma

class CBaseEntity
{
public:

	void* GetClientEntity()
	{
		return GetVirtual<void* (__thiscall*)(void*)>(this, 4)(this);
	}

	int GetIndex()
	{
		void* ptr = GetClientEntity();
		return GetVirtual<int (__thiscall*)(void*)>(ptr, 9)(ptr);
	}

	int GetHealth()
	{
		return *(int*)(this + 0x90/*var.m_iHealth*/);
	}

	bool IsPlayer(ILuaInterface* state)
	{
		if (!state)
			return false;

		return LuaPlayer::IsPlayer(state, GetIndex());
	}

	bool IsAlive(ILuaInterface* state)
	{
		if (!state)
			return false;

		return LuaPlayer::IsAlive(state, GetIndex());
	}

	bool IsDormant(ILuaInterface* state)
	{
		if (!state)
			return false;

		return LuaPlayer::IsDormant(state, GetIndex());
	}

	std::string GetName(ILuaInterface* state)
	{
		if (!state)
			return "unknown";

		return LuaPlayer::GetName(state, GetIndex());
	}

	Color GetTeamColor(ILuaInterface* state)
	{
		if (!state)
			return Color();

		return LuaPlayer::GetTeamColor(state, GetIndex());
	}
};