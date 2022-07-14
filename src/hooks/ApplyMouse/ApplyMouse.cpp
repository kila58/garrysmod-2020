#include "ApplyMouse.hpp"

#include "../src/garrysmod.hpp"

#include "../src/features/features.hpp"

class CUserCmd
{
public:
	//int		header;
	int		command_number;
	int		tick_count;
	Angle  viewangles;
	Vector move;
	int		buttons;
	char	impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousex;
	short	mousey;
	bool	hasbeenpredicted;

	bool GetContextOpen()
	{
		return *(bool*)(this + 0x3F);
	}

	void SetContextOpen(bool open)
	{
		*(bool*)(this + 0x3F) = open;
	}

	Vector GetContextDirection()
	{
		return *(Vector*)(this + 0x40);
	}

	void SetContextDirection(Vector dir)
	{
		*(Vector*)(this + 0x40) = dir;
	}
};

using ApplyMouseType = void(__thiscall*)(void*, Angle&, CUserCmd*, float, float);
ApplyMouseType original_function;

void AngleStep(Angle ang, Angle old)
{
	Vector dif;
	dif.x = std::clamp((ang - old).p, -89.f, 89.f);
	dif.y = std::clamp(normalize((ang - old).y), -180.f, 180.f);

	if (dif.Normalize() > 34)
		ang = old + Angle(dif.x, dif.y, 0) * 34;
}

Vector AnglesToPixels(Angle old, Angle ang, float sensitivity, float m_pitch, float m_yaw)
{
	Angle delta = old - ang;

	float movex = (-delta.p) / (m_pitch * sensitivity * 1);
	float movey = (delta.y) / (m_yaw * sensitivity * 1);

	return Vector(movey, movex, 0.0f);
}

void __fastcall ApplyMouse(void* instance, Angle& viewangles, CUserCmd* cmd, float mouse_x, float mouse_y)
{
	auto cstate = luashared->GetLuaInterface(CLIENT);
	if (!cstate)
		return original_function(instance, viewangles, cmd, mouse_x, mouse_y);

	float m_pitch = LuaMenu::GetCVarFloat(cstate, "m_pitch");
	float m_yaw = LuaMenu::GetCVarFloat(cstate, "m_yaw");
	float sensitivity = LuaMenu::GetCVarFloat(cstate, "sensitivity");

	//1 calculate aimbot angles and set viewangles argument
	//2 call original and pass modified argument to hide from lua callback
	//3 set viewangles again to overwrite calculations from original

	Angle aim;
	for (int i = 1; i < cliententitylist->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* ent = cliententitylist->GetClientEntity(i);
		if (!ent)
			continue;

		if (!LuaBaseEntity::IsPlayer(cstate, i))
			continue;

		Vector pos = LuaBaseEntity::EyePos(cstate, i);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distribution(0.2, -0.2);
		float res = distribution(gen);
		pos += Vector(res, -res, res);

		VectorAngles(pos - LuaBaseEntity::EyePos(cstate, 1), aim);
	}

	AngleStep(aim, viewangles);

	Vector pixels = AnglesToPixels(viewangles, aim, sensitivity, m_pitch, m_yaw);

	mouse_x = round(pixels.x / sensitivity) * sensitivity;
	mouse_y = round(pixels.y / sensitivity) * sensitivity;

	original_function(instance, viewangles, cmd, mouse_x, mouse_y);
}

void ApplyMouseHook::Init()
{
	original_function = (ApplyMouseType)(Memory::SigScan("48 89 5C 24 18 48 89 74 24 20 57 48 83 EC 70 0F B6 81 14 01", "client.dll"));

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)original_function, ApplyMouse);
	DetourTransactionCommit();
}

void ApplyMouseHook::Destroy()
{
	//detour unhook

	delete hook;
}

ApplyMouseHook applymouse_hook;
