#pragma once

void Chams::PlayerModel(CBaseEntity* ent)
{
	if (!LuaMenu::GetSettings<bool>(mstate, "visuals_player_outline"))
		return;

	if (!ent)
		return;

	if (!ent->IsPlayer(cstate))
		return;

	if (!ent->IsAlive(cstate))
		return;

	if (ent->IsDormant(cstate))
		return;

	renderable.push_back(ent);
}