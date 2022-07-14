#pragma once

#include "../features.hpp"

#include "../src/garrysmod.hpp"

class Chams : public BaseFeature
{
public:
	Chams() : BaseFeature(VIEWRENDER, 2u) {} //3d context needs to run before 2d in same hook

	void Init();
	void Invoke();

	void PlayerModel(CBaseEntity* ent);
	void EntModel(CBaseEntity* ent);

private:
	ILuaInterface* cstate;
	ILuaInterface* mstate;

	IMaterial* mat;

	std::vector<CBaseEntity*> renderable;
};

extern Chams chams;
