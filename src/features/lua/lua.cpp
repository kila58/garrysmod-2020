#include "lua.hpp"

ILuaInterface* menu = nullptr;
ILuaInterface* client = nullptr;

int L_entsGetAll(lua_State* L)
{
	client->PushSpecial(0);
	client->GetField(-1, "ents");
	client->GetField(-1, "GetAll");
	client->PCall(0, 1, 0);
	bool exists = client->IsType(-1, Type::TABLE);
	ILuaObject* table = client->GetObject(-1);
	client->Pop(client->Top());

	if (table->isTable())
		MessageBoxA(NULL, NULL, NULL, NULL);

	if (exists)
		menu->PushLuaObject(table);

	return 1;
}

int L_GetEnt(lua_State* state)
{
	if (!menu->IsType(1, Type::NUMBER))
	{
		menu->PushNil();
		return 1;
	}

	CBaseEntity* ent = (CBaseEntity*)cliententitylist->GetClientEntity(menu->GetNumber(1));

	if (!ent)
	{
		menu->PushNil();
		return 1;
	}

	/*ClientClass* cc = ent->GetClientClass();

	if (!cc || !cc->m_pNetworkName)
	{
		menu->PushNil();
		return 1;
	}

	int len = strlen(cc->m_pNetworkName);

	if (1 > len || len > 255)
	{
		menu->PushNil();
		return 1;
	}*/

	UserData* ud = (UserData*)menu->NewUserdata(sizeof(UserData));
	ud->type = Type::ENTITY;
	ud->data = ent;

	menu->CreateMetaTableType("Entity", Type::ENTITY);
	menu->SetMetaTable(-2);

	return 1;
}

int L_chatOpen(lua_State* L)
{
	client->PushSpecial(0);
	client->GetField(-1, "chat");
	client->GetField(-1, "Open");
	client->PushNumber(1);
	client->PCall(1, 0, 0);
	client->Pop(client->Top());

	return 0;
}

int L_ToScreen(lua_State* L)
{
	client->PushSpecial(0);
	client->GetField(-1, "Vector");
	client->PushVector(*(Vector*)(menu->GetUserdata(1)->data));
	client->PCall(1, 1, 0);
	client->Push(-1);
	client->GetField(-1, "ToScreen");
	client->Push(-2);
	client->PCall(1, 1, 0);

	client->PushString("x");
	client->GetTable(-2);
	int x = client->GetNumber(-1);
	client->Pop();

	client->PushString("y");
	client->GetTable(-2);
	int y = client->GetNumber(-1);
	client->Pop();

	Vector screen(x, y, 0);

	menu->PushVector(screen);

	client->PushString("visible");
	client->GetTable(-2);
	bool visible = client->GetBool(-1);
	client->Pop(client->Top());

	menu->PushBool(visible);

	return 2;
}

int L_hookCallBack(lua_State* L)
{
	return 0;
}

int L_hookAddClient(lua_State* L)
{
	client->PushSpecial(0);
	client->GetField(-1, "hook");
	client->GetField(-1, "Add");
	client->PushString(menu->GetString(1));
	client->PushString(menu->GetString(2));
	client->PushCFunction(L_hookCallBack);
	client->PCall(3, 0, 0);
	client->Pop(client->Top());

	return 0;
}

std::string menulua = R"(
local frame = vgui.Create( "DFrame" )
frame:SetTitle( "PaintManual Test" )
frame:SetSize( 500, 500 )
frame:SetPaintedManually( true )

function MenuFrameRender()
	frame:PaintManual()
end

function GetOutlineMat()
	return CreateMaterial("outline", "UnlitGeneric", {
		["$basetexture"] = "white",
		["$wireframe"] = "1",
		["$color2"] = "[2 2 2]",
	})
end
)";

bool Lua::Init()
{
	/*client = luashared->GetLuaInterface(CLIENT);
	if (!client)
		return false;*/

	menu = luashared->GetLuaInterface(MENU);
	if (!menu)
		return false;

	//initalize fonts

	menu->RunString("", "", menulua.c_str(), true, true);

	//menu->RunString("", "", "concommand.Add('menu_run', function(a, b, c, d) RunString(d, '', true) end)", true, true);

	return true;
}

lua_State* Lua::GetState()
{
	return L;
}

int Lua::LoadBuffer(std::string script, std::string name)
{
	auto str = script.c_str();
	return luaL_loadbuffer(L, str, strlen(str), name.c_str());
}

Lua lua;