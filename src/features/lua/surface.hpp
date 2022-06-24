#pragma once

class LuaSurface
{
public:
	static void Start2D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "Start2D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void End2D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "End2D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void Start3D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "Start3D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void End3D(ILuaInterface* state)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "cam");
		state->GetField(-1, "End3D");
		state->PCall(0, 1, 0);

		state->Pop(state->Top());
	}

	static void SetColorModulation(ILuaInterface* state, float r, float g, float b)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetColorModulation");
		state->PushNumber(r);
		state->PushNumber(g);
		state->PushNumber(b);
		state->PCall(3, 1, 0);

		state->Pop(state->Top());
	}

	static void SetBlend(ILuaInterface* state, float blend)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "render");
		state->GetField(-1, "SetBlend");
		state->PushNumber(blend);
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetDrawColor(ILuaInterface* state, int r, int g, int b, int a = 255)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "SetDrawColor");
		state->PushNumber(r);
		state->PushNumber(g);
		state->PushNumber(b);
		state->PushNumber(a);
		state->PCall(4, 1, 0);

		state->Pop(state->Top());
	}

	static void DrawLine(ILuaInterface* state, int startx, int starty, int endx, int  endy)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "DrawLine");
		state->PushNumber(startx);
		state->PushNumber(starty);
		state->PushNumber(endx);
		state->PushNumber(endy);
		state->PCall(4, 1, 0);

		state->Pop(state->Top());
	}

	static void SetFont(ILuaInterface* state, std::string font)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "SetFont");
		state->PushString(font.c_str());
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}

	static void SetTextColor(ILuaInterface* state, int r, int g, int b, int a = 255)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "SetTextColor");
		state->PushNumber(r);
		state->PushNumber(g);
		state->PushNumber(b);
		state->PushNumber(a);
		state->PCall(4, 1, 0);

		state->Pop(state->Top());
	}

	static void SetTextPos(ILuaInterface* state, int x, int y)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "SetTextPos");
		state->PushNumber(x);
		state->PushNumber(y);
		state->PCall(2, 1, 0);

		state->Pop(state->Top());
	}

	static void DrawText(ILuaInterface* state, std::string text)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "DrawText");
		state->PushString(text.c_str());
		state->PCall(1, 1, 0);

		state->Pop(state->Top());
	}
};