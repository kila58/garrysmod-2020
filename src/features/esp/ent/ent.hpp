#pragma once

void ESP::EntESP(CBaseEntity* ent)
{
	static std::string ofilter;
	static std::set<int> filterpass;
	static std::set<int> filterfail;

	if (!ent)
		return;

	if (LuaBaseEntity::GetOwner(cstate, ent->GetIndex()))
		return;

	if (!LuaBaseEntity::IsScripted(cstate, ent->GetIndex()))
		return;

	Vector pos = LuaBaseEntity::GetPos(cstate, ent->GetIndex());
	Vector screen;
	if (!LuaBaseEntity::ToScreen(cstate, pos, screen))
		return;

	std::string name = LuaBaseEntity::GetClass(cstate, ent->GetIndex());
	std::string filter = LuaMenu::GetSettings<std::string>(mstate, "visuals_entity_filter");
	if (filter.length() > 0)
	{
		if (filter != ofilter)
		{
			filterpass.clear();
			filterfail.clear();
			ofilter = filter;
		}
		else
		{
			int id = ent->GetIndex();
			if (!filterfail.contains(id))
			{
				if (!filterpass.contains(id))
				{
					if (strstr(name.c_str(), filter.c_str()))
						filterpass.insert(id);
					else
					{
						filterfail.insert(id);
						return;
					}
				}
			}
			else
				return;
		}
	}

	auto hex = LuaMenu::GetSettings<std::string>(mstate, "visuals_entity_color");
	Color col = HexToRGB(hex, true);

	int x, y, w, h;
	if (GetBoundingBox(cstate, ent, x, y, w, h))
	{
		if (LuaMenu::GetSettings<bool>(mstate, "visuals_entity_box"))
			OutlinedRectangle(cstate, x, y, w, h, Color(col.r, col.g, col.b, 232), true);

		if (LuaMenu::GetSettings<bool>(mstate, "visuals_entity_name"))
			DrawString(mstate, true, true, x + (w * 0.5), y - 7, Color(255, 255, 255, 255), name);
	}
}