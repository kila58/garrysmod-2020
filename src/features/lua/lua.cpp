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
	ILuaObject* table = client->GetObjectA(-1);
	client->Pop(client->Top());

	if (table->isTable())
		MessageBoxA(NULL, NULL, NULL, NULL);

	if (exists)
		menu->PushLuaObject(table);

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

bool Lua::Init()
{
	typedef void* (*CreateInterface_t)(const char* name, int* pReturnCode);
	CreateInterface_t CreateInterface = (CreateInterface_t)GetProcAddress(GetModuleHandle("lua_shared.dll"), "CreateInterface");

	int bruh = 0;
	luashared = (LuaShared*)CreateInterface("LUASHARED003", &bruh);
	if (!luashared)
		return false;

	client = luashared->GetLuaInterface(CLIENT);
	if (!client)
		return false;

	menu = luashared->GetLuaInterface(MENU);
	if (!menu)
		return false;

	/*menu->PushSpecial(0);
	menu->CreateTable();
	menu->PushCFunction(L_entsGetAll);
	menu->SetField(-2, "GetAll");
	menu->SetField(-2, "ents");
	menu->Pop(menu->Top());*/

	menu->PushSpecial(0);
	menu->PushCFunction(L_chatOpen);
	menu->SetField(-2, "ChatOpen");
	menu->Pop(menu->Top());

	menu->PushSpecial(0);
	menu->GetField(-1, "FindMetaTable");
	menu->PushString("Vector", 0);
	menu->PCall(1, 1, 0);
	menu->PushCFunction(L_ToScreen);
	menu->SetField(-2, "ToScreen");
	menu->Pop(menu->Top());

	menu->RunString("", "", "concommand.Add('menu_run', function(a, b, c, d) RunString(d, '', true) end)", true, true);

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