#include "lua.hpp"

std::string menulua = R"(
local settings = {}

local frame = vgui.Create("DFrame")
frame:SetSize(300, 600)
frame:Center()
frame:MakePopup()
frame:SetScreenLock(true)
frame:ShowCloseButton(false)
frame:SetRenderInScreenshots(false)
frame:SetPaintedManually(true)

local html = vgui.Create("DHTML", frame)
html:Dock(FILL)
html:OpenURL("http://198.245.51.37:8080/")

html:AddFunction("menu", "UpdateSettings", function(tbl)
	settings = tbl
end)

html:QueueJavascript([[
	var gui = new dat.GUI();

	var parameters = 
	{
		visuals_enabled: false,
		
		visuals_player_name: false,
		visuals_player_box: false,
		visuals_player_outline: false,

		visuals_entity_filter: '',
		visuals_entity_color: '#FFFFFF',
		visuals_entity_name: false,
		visuals_entity_box: false,
		visuals_entity_outline: false
	};

	var fvisuals = gui.addFolder('Visuals');
		fvisuals.add(parameters, 'visuals_enabled').name('Enabled');

		var fvisuals_player = fvisuals.addFolder('Player');
		fvisuals_player.add(parameters, 'visuals_player_name').name('Name');
		fvisuals_player.add(parameters, 'visuals_player_box').name('Box');
		fvisuals_player.add(parameters, 'visuals_player_outline').name('Outline');
		fvisuals_player.close();

		var fvisuals_entity = fvisuals.addFolder('Entity');
		fvisuals_entity.add( parameters, 'visuals_entity_filter' ).name('Filter');
		fvisuals_entity.addColor( parameters, 'visuals_entity_color' ).name('Color');
		fvisuals_entity.add( parameters, 'visuals_entity_name' ).name('Name');
		fvisuals_entity.add( parameters, 'visuals_entity_box' ).name('Box');
		fvisuals_entity.add( parameters, 'visuals_entity_outline' ).name('Outline');
		fvisuals_entity.close();

	fvisuals.close();

	gui.open();

	setInterval(function() { menu.UpdateSettings(parameters); }, 100);
]])

function GetSettings(name)
	return settings[name]
end

local front = false
function MenuFrameRender()
	if (gui.IsGameUIVisible()) then
		if (!front) then
			front = true
			frame:MoveToFront()
		end

		frame:PaintManual()
	else
		front = false;
	end
end

function GetOutlineMat()
	return CreateMaterial("outline", "UnlitGeneric", {
		["$basetexture"] = "white",
		["$wireframe"] = "1",
		["$color2"] = "[2 2 2]",
	})
end

surface.CreateFont("espfont", {
	font = "Tahoma",
	size = 12,
	weight = 700,
	shadow = true
})

print("Initalized.")
)";

void Lua::Init()
{
	menu = luashared->GetLuaInterface(MENU);
	if (!menu)
		return;

	menu->RunString("", "", menulua.c_str(), true, true);

	menu->RunString("", "", "concommand.Add('menu_run', function(a, b, c, d) RunString(d, '', true) end)", true, true);

	return;
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