#pragma once

class LuaSurface
{
public:
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

	static void DrawOutlinedRect(ILuaInterface* state, int x, int y, int w, int h, int thickness)
	{
		if (!state)
			return;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "DrawOutlinedRect");
		state->PushNumber(x);
		state->PushNumber(y);
		state->PushNumber(w);
		state->PushNumber(h);
		state->PushNumber(thickness);
		state->PCall(5, 1, 0);

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

	static void GetTextSize(ILuaInterface* state, std::string str, int& w, int& h)
	{
		if (!state)
			return ;

		state->PushSpecial(0);
		state->GetField(-1, "surface");
		state->GetField(-1, "GetTextSize");
		state->PushString(str.c_str());
		state->PCall(1, 2, 0);

		w = state->GetNumber(-2);
		h = state->GetNumber(-1);
		state->Pop(state->Top());
	}

	static int ScreenWidth(ILuaInterface* state)
	{
		if (!state)
			return 0;

		state->PushSpecial(0);
		state->GetField(-1, "ScrW");
		state->PCall(0, 1, 0);

		int res = state->GetNumber();
		state->Pop(state->Top());

		return res;
	}

	static int ScreenHeight(ILuaInterface* state)
	{
		if (!state)
			return 0;

		state->PushSpecial(0);
		state->GetField(-1, "ScrH");
		state->PCall(0, 1, 0);

		int res = state->GetNumber();
		state->Pop(state->Top());

		return res;
	}
};