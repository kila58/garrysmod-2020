#include "esp.hpp"

#include "draw.hpp"

#include "player/player.hpp"
#include "ent/ent.hpp"

void ESP::Init()
{

}

void ESP::Invoke()
{
	cstate = luashared->GetLuaInterface(CLIENT);
	if (!cstate)
		return;

	mstate = luashared->GetLuaInterface(MENU);
	if (!mstate)
		return;

	LuaRender::Start2D(cstate);

	for (int i = 0; i < cliententitylist->GetHighestEntityIndex(); i++)
	{
		if (!LuaMenu::GetSettings<bool>(mstate, "visuals_enabled")) //in loop until menu is moved out of this feature
			continue;

		CBaseEntity* ent = cliententitylist->GetClientEntity(i);
		if (!ent)
			continue;

		if (ent->IsLocalPlayer(cstate))
			continue;

		EntESP(ent);
		PlayerESP(ent);
	}

	mstate->PushSpecial(0);
	mstate->GetField(-1, "MenuFrameRender");
	mstate->PCall(0, 1, 0);
	mstate->Pop(mstate->Top());

	LuaRender::End2D(cstate);
}

ESP esp;