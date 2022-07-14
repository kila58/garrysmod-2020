#pragma once

void Chams::EntModel(CBaseEntity* ent)
{
	if (!LuaMenu::GetSettings<bool>(mstate, "visuals_entity_outline"))
		return;

	static std::string ofilter;
	static std::set<int> filterpass;
	static std::set<int> filterfail;

	if (!ent)
		return;

	if (LuaBaseEntity::GetOwner(cstate, ent->GetIndex()))
		return;

	if (!LuaBaseEntity::IsScripted(cstate, ent->GetIndex()))
		return;

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
					std::string name = LuaBaseEntity::GetClass(cstate, ent->GetIndex());
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

	renderable.push_back(ent);
}