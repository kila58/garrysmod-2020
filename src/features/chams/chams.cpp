#include "chams.hpp"

#include "ent/ent.hpp"
#include "player/player.hpp"

void Chams::Init()
{

}

void ResetStencilState(ILuaInterface* state)
{
	LuaRender::SetStencilWriteMask(state, 0xFF);
	LuaRender::SetStencilTestMask(state, 0xFF);
	LuaRender::SetStencilReferenceValue(state, 0);
	LuaRender::SetStencilPassOperation(state, 1);
	LuaRender::SetStencilZFailOperation(state, 1);
	LuaRender::ClearStencil(state);
}

void Chams::Invoke()
{
	cstate = luashared->GetLuaInterface(CLIENT);
	if (!cstate)
		return;

	mstate = luashared->GetLuaInterface(MENU);
	if (!mstate)
		return;

	if (!LuaMenu::GetSettings<bool>(mstate, "visuals_enabled"))
		return;

	if (!LuaMenu::GetSettings<bool>(mstate, "visuals_entity_outline") && !LuaMenu::GetSettings<bool>(mstate, "visuals_player_outline"))
		return;

	if (!mat)
	{
		mstate->PushSpecial(0);
		mstate->GetField(-1, "GetOutlineMat");
		mstate->PCall(0, 1, 0);

		mat = (IMaterial*)mstate->GetObject(-1)->GetUserData();
		mstate->Pop(mstate->Top());
	}

	renderable.clear();

	for (int i = 0; i < cliententitylist->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* ent = cliententitylist->GetClientEntity(i);
		if (!ent)
			continue;

		if (ent->IsLocalPlayer(cstate))
			continue;

		EntModel(ent);
		PlayerModel(ent);
	}

	LuaRender::Start3D(cstate);

	ResetStencilState(cstate);

	LuaRender::SetStencilEnable(cstate, true);

	LuaRender::SuppressEngineLighting(cstate, true);

	LuaRender::SetStencilReferenceValue(cstate, 1);
	LuaRender::SetStencilCompareFunction(cstate, 1);
	LuaRender::SetStencilFailOperation(cstate, 3);

	for (auto ent : renderable)
	{
		if (!ent)
			continue;

		enginemodel->ForceMaterialOverride(nullptr);

		LuaRender::SetBlend(cstate, 0);
		LuaRender::SetColorModulation(cstate, 0, 0, 0);

		ent->DrawModel();

		LuaRender::SetBlend(cstate, 1);
		LuaRender::SetColorModulation(cstate, 1, 1, 1);
	}

	LuaRender::SetStencilCompareFunction(cstate, 6);
	LuaRender::SetStencilFailOperation(cstate, 1);

	for (auto ent : renderable)
	{
		if (!ent)
			continue;

		enginemodel->ForceMaterialOverride(mat);

		Color col;
		if (!ent->IsPlayer(cstate))
			col = HexToRGB(LuaMenu::GetSettings<std::string>(mstate, "visuals_entity_color"), true);
		else
			col = ent->GetTeamColor(cstate);

		LuaRender::SetColorModulation(cstate, col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);

		ent->DrawModel();

		LuaRender::SetColorModulation(cstate, 1, 1, 1);

		enginemodel->ForceMaterialOverride(nullptr);
	}

	LuaRender::SuppressEngineLighting(cstate, false);

	LuaRender::SetStencilEnable(cstate, false);

	ResetStencilState(cstate);

	LuaRender::End3D(cstate);

	renderable.clear();
}

Chams chams;