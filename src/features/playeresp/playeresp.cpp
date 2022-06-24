#include "playeresp.hpp"

using View_RenderType = void* (__thiscall*)(void*, void*);
View_RenderType original_function;

void __fastcall View_Render(void* instance, void* rect)
{
	original_function(instance, rect);

	static Material* mat;
	if (!mat)
	{
		mat = materialsystem->CreateMaterial("models/debug/debugwhite");

		if (mat)
		{
			mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, true);
			mat->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, true);
			mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			mat->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
			mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
			mat->IncrementReferenceCount();
		}
	}

	auto cstate = luashared->GetLuaInterface(CLIENT);
	if (!cstate)
		return;

	auto mstate = luashared->GetLuaInterface(MENU);
	if (!mstate)
		return;

	LuaSurface::Start3D(cstate);

	for (int i = 0; i <= LuaPlayer::GetCount(cstate); i++)
	{
		CBaseEntity* ent = cliententitylist->GetClientEntity(i);
		if (!ent)
			continue;

		if (!ent->IsPlayer(cstate))
			continue;

		if (!ent->IsAlive(cstate))
			continue;

		if (ent->IsDormant(cstate))
			continue;

		Color team = ent->GetTeamColor(cstate);

		enginemodel->ForceMaterialOverride(mat);

		mat->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
		mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, true);
		mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);

		LuaSurface::SetBlend(cstate, 1);
		LuaSurface::SetColorModulation(cstate, team.r / 255.0f, team.g / 255.0f, team.b / 255.0f);

		LuaPlayer::DrawModel(cstate, i, 32);

		mat->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, false);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);
		mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

		enginemodel->ForceMaterialOverride(nullptr);

		LuaPlayer::DrawModel(cstate, i, 32);

		//LuaSurface::SetColorModulation(cstate, 1.0f, 1.0f, 1.0f);
		//LuaPlayer::DrawModel(cstate, i, 32);
	}

	LuaSurface::End3D(cstate);

	LuaSurface::Start2D(cstate);

	for (int i = 0; i <= LuaPlayer::GetCount(cstate); i++)
	{
		CBaseEntity* ent = cliententitylist->GetClientEntity(i);
		if (!ent)
			continue;

		if (!ent->IsPlayer(cstate))
			continue;

		if (!ent->IsAlive(cstate))
			continue;

		if (ent->IsDormant(cstate))
			continue;

		std::string name = ent->GetName(cstate);

		Color team = ent->GetTeamColor(cstate);

		Vector pos = LuaPlayer::GetPos(cstate, i);
		Vector screen = LuaPlayer::ToScreen(cstate, pos);

		LuaSurface::SetFont(mstate, "Default");
		LuaSurface::SetTextColor(mstate, team.r, team.g, team.b);
		LuaSurface::SetTextPos(mstate, screen.x, screen.y);
		LuaSurface::DrawText(mstate, LuaPlayer::GetName(cstate, i));
	}

	//LuaSurface::SetDrawColor(cstate, 255, 255, 255);
	//LuaSurface::DrawLine(cstate, 0, 0, 200, 200);

	LuaSurface::End2D(cstate);
}

bool PlayerESP::Init()
{
	hook = new Hook(clientinterface, 26, &View_Render);
	original_function = (View_RenderType)hook->ReplaceVirtual();

	return true;
}

PlayerESP playeresp;