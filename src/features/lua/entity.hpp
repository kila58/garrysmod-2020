#pragma once

class LuaBaseEntity
{
public:
	static int GetCount(ILuaInterface* state) //doesn't return true entity count ??
	{
		if (!state)
			return 0;

		state->PushSpecial(0);
		state->GetField(-1, "ents");
		state->GetField(-1, "GetCount");
		state->PushBool(true);
		state->PCall(1, 1, 0);

		int res = state->GetNumber();
		state->Pop(state->Top());

		return res;
	}

	static void* LocalPlayer(ILuaInterface* state)
	{
		if (!state)
			return nullptr;

		state->PushSpecial(0);
		state->GetField(-1, "LocalPlayer");
		state->PCall(0, 1, 0);

		void* res = (void*)state->GetObject(-1)->GetUserData(); // CBaseEntity*
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

	static bool IsWeapon(ILuaInterface* state, int index)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "IsWeapon");
		state->Push(-2);
		state->PCall(1, 1, 0);

		bool res = state->GetBool();
		state->Pop(state->Top());

		return res;
	}

	static bool IsScripted(ILuaInterface* state, int index)
	{
		if (!state)
			return false;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "IsScripted");
		state->Push(-2);
		state->PCall(1, 1, 0);

		bool res = state->GetBool();
		state->Pop(state->Top());

		return res;
	}

	static void* GetOwner(ILuaInterface* state, int index)
	{
		if (!state)
			return nullptr;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetOwner");
		state->Push(-2);
		state->PCall(1, 1, 0);

		//bool res = lua_isnoneornil(state->GetState(), -1);
		void* res = (void*)state->GetObject(-1)->GetUserData(); // CBaseEntity*
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

	static std::string GetClass(ILuaInterface* state, int index)
	{
		if (!state)
			return "unknown";

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetClass");
		state->Push(-2);
		state->PCall(1, 1, 0);

		std::string res = state->GetString();
		state->Pop(state->Top());

		return res;
	}

	static Angle GetAngles(ILuaInterface* state, int index)
	{
		if (!state)
			return Angle();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetAngles");
		state->Push(-2);
		state->PCall(1, 1, 0);

		Angle res = *(Angle*)state->GetObject(-1)->GetUserData();
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

	static Vector EyePos(ILuaInterface* state, int index)
	{
		if (!state)
			return Vector();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "EyePos");
		state->Push(-2);
		state->PCall(1, 1, 0);

		Vector res = *(Vector*)state->GetObject(-1)->GetUserData();
		state->Pop(state->Top());

		return res;
	}

	static Vector OBBCenter(ILuaInterface* state, int index)
	{
		if (!state)
			return Vector();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "OBBCenter");
		state->Push(-2);
		state->PCall(1, 1, 0);

		Vector res = *(Vector*)state->GetObject(-1)->GetUserData();
		state->Pop(state->Top());

		return res;
	}

	static Vector OBBMins(ILuaInterface* state, int index)
	{
		if (!state)
			return Vector();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "OBBMins");
		state->Push(-2);
		state->PCall(1, 1, 0);

		Vector res = *(Vector*)state->GetObject(-1)->GetUserData();
		state->Pop(state->Top());

		return res;
	}

	static Vector OBBMaxs(ILuaInterface* state, int index)
	{
		if (!state)
			return Vector();

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "OBBMaxs");
		state->Push(-2);
		state->PCall(1, 1, 0);

		Vector res = *(Vector*)state->GetObject(-1)->GetUserData();
		state->Pop(state->Top());

		return res;
	}

	static void GetCollisionBounds(ILuaInterface* state, int index, Vector& min, Vector& max)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "Entity");
		state->PushNumber(index);
		state->PCall(1, 1, 0);
		state->Push(-1);
		state->GetField(-1, "GetCollisionBounds");
		state->Push(-2);
		state->PCall(1, 2, 0);

		min = *(Vector*)state->GetObject(-2)->GetUserData();
		max = *(Vector*)state->GetObject(-1)->GetUserData();
		state->Pop(state->Top());
	}

	static bool ToScreen(ILuaInterface* state, Vector world, Vector& screen)
	{
		if (!state)
			return false;

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

		screen = Vector(x, y, 0);

		state->PushString("visible");
		state->GetTable(-2);
		bool res = state->GetBool(-1);
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