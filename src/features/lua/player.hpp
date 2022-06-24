#pragma once

class LuaPlayer
{
public:
	static int GetCount(ILuaInterface* state)
	{
		if (!state)
			return 0;

		state->PushSpecial(0);
		state->GetField(-1, "player");
		state->GetField(-1, "GetCount");
		state->PCall(0, 1, 0);

		int res = state->GetNumber();
		state->Pop(state->Top());

		return res;
	}

	static bool IsPlayer(ILuaInterface* state, int index)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "IsPlayer");
		state->Push(-2);
		state->PCall(1, 1, 0);

		bool res = state->GetBool();
		state->Pop(state->Top());

		return res;
	}

	static bool IsAlive(ILuaInterface* state, int index)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "Alive");
		state->Push(-2);
		state->PCall(1, 1, 0);

		bool res = state->GetBool();
		state->Pop(state->Top());

		return res;
	}

	static bool IsDormant(ILuaInterface* state, int index)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "IsDormant");
		state->Push(-2);
		state->PCall(1, 1, 0);

		bool res = state->GetBool();
		state->Pop(state->Top());

		return res;
	}

	static std::string GetName(ILuaInterface* state, int index)
	{
		if (!state)
			return "unknown";

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetName");
		state->Push(-2);
		state->PCall(1, 1, 0);

		std::string res = state->GetString();
		state->Pop(state->Top());

		return res;
	}

	static Vector GetPos(ILuaInterface* state, int index)
	{
		if (!state)
			return Vector();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetPos");
		state->Push(-2);
		state->PCall(1, 1, 0);

		Vector res = *(Vector*)state->GetObject(-1)->GetUserData(); //GetVector doesn't work??
		state->Pop(state->Top());

		return res;
	}

	static Vector ToScreen(ILuaInterface* state, Vector world)
	{
		if (!state)
			return Vector();

		state->PushSpecial(0);
		state->GetField(-1, "Vector");
		state->PushVector(world);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "ToScreen");
		state->Push(-2);
		state->PCall(1, 1, 0);

		state->PushString("x");
		state->GetTable(-2);
		int x = state->GetNumber(-1);
		state->Pop();

		state->PushString("y");
		state->GetTable(-2);
		int y = state->GetNumber(-1);
		state->Pop();

		Vector res(x, y, 0);
		state->Pop(state->Top());

		return res;
	}

	static void DrawModel(ILuaInterface* state, int index, int flag)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "DrawModel");
		state->Push(-2);
		//state->PushNumber(flag);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static Color GetTeamColor(ILuaInterface* state, int index)
	{
		if (!state)
			return Color();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->Call(1, 1);
		state->PushSpecial(0);
		state->GetField(-1, "GAMEMODE");
		state->GetField(-1, "GetTeamColor");
		state->Push(-2);
		state->Push(-5);
		state->Call(2, 1);
		state->GetField(-1, "r");
		int r = state->GetNumber(-1);
		state->Pop(1);
		state->GetField(-1, "g");
		int g = state->GetNumber(-1);
		state->Pop(1);
		state->GetField(-1, "b");
		int b = state->GetNumber(-1);
		state->Pop(state->Top());

		Color res = Color(r, g, b, 255);

		return res;
	}
};