#pragma once

void ESP::PlayerESP(CBaseEntity* ent)
{
	if (!ent)
		return;

	if (!ent->IsPlayer(cstate))
		return;

	if (!ent->IsAlive(cstate))
		return;

	if (ent->IsDormant(cstate))
		return;

	std::string name = ent->GetName(cstate);

	Color team = ent->GetTeamColor(cstate);

	int x, y, w, h;
	if (GetBoundingBox(cstate, ent, x, y, w, h))
	{
		if (LuaMenu::GetSettings<bool>(mstate, "visuals_player_box"))
			OutlinedRectangle(cstate, x, y, w, h, Color(team.r, team.g, team.b, 232), true);

		if (LuaMenu::GetSettings<bool>(mstate, "visuals_player_name"))
			DrawString(mstate, true, true, x + (w * 0.5), y - 7, Color(255, 255, 255, 255), name);
	}
}