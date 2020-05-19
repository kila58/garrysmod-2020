#pragma once

class Color
{
public:
	inline Color() : r(255), g(255), b(255), a(255) {}
	inline Color(int r, int g, int b) : r(r), g(g), b(b), a(255) {}
	inline Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

	unsigned char r, g, b, a;
};

class RGB
{
public:
	float r, g, b;
};

inline Color HSVtoRGB(float h, float s, float v)
{
	if (s == 0.0f)
		return Color((int)std::floorf(v * 255), (int)std::floorf(v * 255), (int)std::floorf(v * 255));

	RGB out;

	if (h >= 360.0f)
		h = 0.0f;

	h /= 60.0f;

	int high = (int)h;
	float f = h - high;

	float p = v * (1.0f - s);
	float q = v * (1.0f - (s * f));
	float t = v * (1.0f - (s * (1.0f - f)));

	switch (high)
	{
	case 0:
		out.r = v; out.g = t; out.b = p;
		break;
	case 1:
		out.r = q; out.g = v; out.b = p;
		break;
	case 2:
		out.r = p; out.g = v; out.b = t;
		break;
	case 3:
		out.r = p; out.g = q; out.b = v;
		break;
	case 4:
		out.r = t; out.g = p; out.b = v;
		break;
	default:
		out.r = v; out.g = p; out.b = q;
		break;
	}

	return Color((int)std::floorf(out.r * 255), (int)std::floorf(out.g * 255), (int)std::floorf(out.b * 255));
}
