#pragma once

class LuaMenu
{
public:
	template<typename T>
	static T GetSettings(ILuaInterface* state, std::string name)
	{
		if (!state)
			return T();

		state->PushSpecial(0);
		state->GetField(-1, "GetSettings");
		state->PushString(name.c_str());
		state->PCall(1, 1, 0);

		T res;

		if constexpr (std::is_same<T, bool>::value)
			res =  state->GetBool();
		else if constexpr (std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, uint32_t>::value)
			res = state->GetNumber();
		else if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const char*>::value)
			res = state->GetString();

		state->Pop(state->Top());

		return res;
	}

	static int GetCVarInt(ILuaInterface* state, std::string convar)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "GetConVar");
		state->PushString(convar.c_str());
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetInt");
		state->Push(-2);
		state->PCall(1, 1, 0);

		int res = state->GetNumber();
		state->Pop(state->Top());

		return res;
	}

	static float GetCVarFloat(ILuaInterface* state, std::string convar)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "GetConVar");
		state->PushString(convar.c_str());
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetFloat");
		state->Push(-2);
		state->PCall(1, 1, 0);

		float res = state->GetNumber();
		state->Pop(state->Top());

		return res;
	}
};