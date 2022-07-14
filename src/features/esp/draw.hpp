#pragma once

bool GetBoundingBox(ILuaInterface* state, CBaseEntity* ent, int& x, int& y, int& w, int& h)
{
	Vector min = ent->OBBMins();
	Vector max = ent->OBBMaxs();

	VMatrix trans = ent->GetWorldTransformMatrix();

	Vector corners[8] =
	{
		Vector(min.x, min.y, min.z),
		Vector(min.x, min.y, max.z),
		Vector(min.x, max.y, min.z),
		Vector(min.x, max.y, max.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, min.y, max.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, max.y, max.z)
	};

	int screenw = LuaSurface::ScreenWidth(state);
	int screenh = LuaSurface::ScreenHeight(state);

	x = screenw;
	y = screenh;
	w = -screenw;
	h = -screenh;

	Vector screen[8];
	for (int i = 0; i < 8; i++)
	{
		VectorRotate3x4(corners[i], trans, corners[i]);

		if (LuaBaseEntity::ToScreen(state, corners[i], screen[i]))
		{
			x = min(x, screen[i].x);
			y = min(y, screen[i].y);
			w = max(w, screen[i].x);
			h = max(h, screen[i].y);
		}
		else
			return false;
	}

	w -= x;
	h -= y;

	return true;
}

/*bool GetBoundingBox(ILuaInterface* state, CBaseEntity* ent, int& x, int& y, int& w, int& h)
{
	static const Vector edges[4] =
	{
		Vector(1.0f, 1.0f, 1.0f),
		Vector(-1.0f, 1.0f, 1.0f),
		Vector(1.0f, -1.0f, 1.0f),
		Vector(-1.0f, -1.0f, 1.0f),
	};

	Vector origin = LuaBaseEntity::GetPos(state, ent->GetIndex());

	Angle rot;
	if (LuaBaseEntity::IsPlayer(state, ent->GetIndex())) //only need yaw
		rot = Angle(0, LuaBaseEntity::GetAngles(state, ent->GetIndex()).y, 0);
	else
		rot = LuaBaseEntity::GetAngles(state, ent->GetIndex());

	//Vector mins = LuaBaseEntity::OBBMins(state, ent->GetIndex()),
		//maxs = LuaBaseEntity::OBBMaxs(state, ent->GetIndex());
	Vector mins, maxs;
	LuaBaseEntity::GetCollisionBounds(state, ent->GetIndex(), mins, maxs);

	int screenw = LuaSurface::ScreenWidth(state),
		screenh = LuaSurface::ScreenHeight(state);

	x = screenw;
	y = screenh;
	w = -screenw;
	h = -screenh;

	for (int i = 0; i < 4; i++)
	{
		Vector mins2d, maxs2d;

		if (!LuaBaseEntity::ToScreen(state, origin + (mins * edges[i].Rotate(rot)), mins2d))
			return false;

		if (!LuaBaseEntity::ToScreen(state, origin + (maxs * edges[i].Rotate(rot)), maxs2d))
			return false;

		x = min(x, (int)ceil(min(mins2d.x, maxs2d.x)));
		y = min(y, (int)ceil(min(mins2d.y, maxs2d.y)));
		w = max(w, (int)ceil(max(mins2d.x, maxs2d.x)));
		h = max(h, (int)ceil(max(mins2d.y, maxs2d.y)));
	}

	w -= x;
	h -= y;

	return true;
}*/

void DrawString(ILuaInterface* state, bool centerx, bool centery, int x, int y, Color color, std::string str, ...)
{
	int wide, tall;
	LuaSurface::GetTextSize(state, str, wide, tall);

	if (centerx)
		x -= wide / 2;

	if (centery)
		y -= tall / 2;

	LuaSurface::SetFont(state, "espfont");
	LuaSurface::SetTextColor(state, color.r, color.g, color.b, color.a);
	LuaSurface::SetTextPos(state, x, y);
	LuaSurface::DrawText(state, str);
}

void OutlinedRectangle(ILuaInterface* state, int x, int y, int w, int h, Color colColor, bool lightoutline)
{
	if (lightoutline)
		LuaSurface::SetDrawColor(state, 10, 10, 10, 115);
	else
		LuaSurface::SetDrawColor(state, 10, 10, 10, 255);

	LuaSurface::DrawOutlinedRect(state, x - 1, y - 1, w + 2, h + 2, 1);
	LuaSurface::DrawOutlinedRect(state, x + 1, y + 1, w - 2, h - 2, 1);
	LuaSurface::SetDrawColor(state, colColor.r, colColor.g, colColor.b, colColor.a);
	LuaSurface::DrawOutlinedRect(state, x, y, w, h, 1);
}