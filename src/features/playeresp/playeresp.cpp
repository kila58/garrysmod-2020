#include "playeresp.hpp"

using View_RenderType = void* (__thiscall*)(void*, void*);
View_RenderType original_function;

void __fastcall View_Render(void* instance, void* rect)
{
	original_function(instance, rect);

	auto cstate = luashared->GetLuaInterface(CLIENT);
	if (!cstate)
		return;

	auto mstate = luashared->GetLuaInterface(MENU);
	if (!mstate)
		return;

	static Material* mat;
	if (!mat)
	{
		mstate->PushSpecial(0);
		mstate->GetField(-1, "GetOutlineMat");
		mstate->PCall(0, 1, 0);

		mat = (Material*)mstate->GetObject(-1)->GetUserData();
		mstate->Pop(mstate->Top());

		//mat = materialsystem->CreateMaterial("models/debug/debugwhite");

		if (mat)
		{
			//mat->SetMaterialVarFlag(MATERIAL_VAR_ALPHATEST, true);
			//mat->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, true);
			//mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			//mat->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
			//mat->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
			mat->IncrementReferenceCount();
		}
	}

	LuaRender::Start3D(cstate);

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

		LuaRender::SetStencilEnable(cstate, true);

		LuaRender::SetStencilReferenceValue(cstate, 1);
		LuaRender::SetStencilCompareFunction(cstate, 1);
		LuaRender::SetStencilFailOperation(cstate, 3);

		enginemodel->ForceMaterialOverride(nullptr);

		LuaRender::SetBlend(cstate, 0);
		LuaRender::SetColorModulation(cstate, 0, 0, 0);

		LuaPlayer::DrawModel(cstate, i, 32);

		LuaRender::SetBlend(cstate, 1);
		LuaRender::SetColorModulation(cstate, 1, 1, 1);

		LuaRender::SetStencilCompareFunction(cstate, 6);
		LuaRender::SetStencilFailOperation(cstate, 1);

		enginemodel->ForceMaterialOverride(mat);

		LuaRender::SetColorModulation(cstate, team.r / 255.0f, team.g / 255.0f, team.b / 255.0f);

		LuaPlayer::DrawModel(cstate, i, 32);

		enginemodel->ForceMaterialOverride(nullptr);

		LuaRender::SetStencilEnable(cstate, false);
	}

	LuaRender::End3D(cstate);

	LuaRender::Start2D(cstate);

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

	//mstate->PushSpecial(0);
	//mstate->GetField(-1, "MenuFrameRender");
	//mstate->PCall(0, 1, 0);
	//mstate->Pop(mstate->Top());

	//LuaSurface::SetDrawColor(cstate, 255, 255, 255);
	//LuaSurface::DrawLine(cstate, 0, 0, 200, 200);

	LuaRender::End2D(cstate);
}

bool PlayerESP::Init()
{
	hook = new Hook(clientinterface, 26, &View_Render);
	original_function = (View_RenderType)hook->ReplaceVirtual();

	return true;
}

PlayerESP playeresp;