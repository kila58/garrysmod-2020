#pragma once

#include "../features.hpp"

#include "../src/garrysmod.hpp"

class ESP : public BaseFeature
{
public:
	ESP() : BaseFeature(VIEWRENDER, 2u) {}

	void Init();
	void Invoke();

	void PlayerESP(CBaseEntity* ent);
	void EntESP(CBaseEntity* ent);

private:
	ILuaInterface* cstate;
	ILuaInterface* mstate;
};

extern ESP esp;