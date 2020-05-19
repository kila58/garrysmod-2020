#pragma once

inline float normalize(const float& f)
{
	return std::remainderf(f, 360.f);
}

class Angle
{
public:
	Angle() : p(0), y(0), r(0) {}
	Angle(float p, float y, float r) : p(p), y(y), r(r) {}

	float p, y, r;

	// todo: just add all of them
	Angle operator-(const Angle&) const;
	Angle& operator-=(const Angle&);
	Angle operator-(const float) const;
	Angle operator*(const float) const;
	Angle operator+(const Angle&) const;
	Angle& operator+=(const Angle&);
};

inline Angle Angle::operator-(const Angle& ang) const
{
	return Angle(p - ang.p, y - ang.y, r - ang.r);
}

inline Angle& Angle::operator-=(const Angle& ang)
{
	p -= ang.p;
	y -= ang.y;
	r -= ang.r;

	return *this;
}

inline Angle Angle::operator-(const float f) const
{
	return Angle(p - f, y - f, r - f);
}

inline Angle Angle::operator*(const float f) const
{
	return Angle(p * f, y * f, r * f);
}

inline Angle Angle::operator+(const Angle& ang) const
{
	return Angle(p + ang.p, y + ang.y, r + ang.r);
}

inline Angle& Angle::operator+=(const Angle& ang)
{
	p += ang.p;
	y += ang.y;
	r += ang.r;

	return *this;
}
