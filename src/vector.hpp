#pragma once

static const float pi = 3.14159265358979323846f;
static const float epsilon = 1.401298e-45f;

class VMatrix
{
public:
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

	float m[3][4];
};

class Quaternion
{
public:
	float x, y, z, w;
};

class Vector
{
public:
	Vector() : x(0), y(0), z(0) {}
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}

	float x, y, z;

	float& operator[](int);
	float const operator[](int) const;

	// todo: just add all of them
	Vector operator-(const Vector&) const;
	Vector& operator-=(const Vector&);
	Vector operator-(const float) const;
	Vector operator/(const float) const;
	Vector& operator/=(const float);
	Vector operator*(const float) const;
	Vector& operator*=(const float);
	Vector operator*(const Vector&) const;
	Vector operator+(const Vector&) const;
	Vector& operator+=(const Vector&);
	Vector operator+(const float) const;
	bool operator==(const Vector&) const;

	void Init(const float, const float, const float);

	bool IsZero() const;

	float Length() const;
	float Length2D() const;
	float LengthSqr() const;
	float Length2DSqr() const;
	float Distance(const Vector&) const;
	float Distance2D(const Vector&) const;
	float Distance2DSqr(const Vector&) const;
	Vector Cross(const Vector&) const;
	float Dot(const Vector&) const;
	float Normalize();
	float NormalizeInPlace();
	Vector Rotate(const Angle&) const;
};

inline float& Vector::operator[](int index)
{
	return ((float*)this)[index];
}

inline float const Vector::operator[](int index) const
{
	return ((float*)this)[index];
}

inline Vector Vector::operator-(const Vector& vec) const
{
	return Vector(x - vec.x, y - vec.y, z - vec.z);
}

inline Vector& Vector::operator-=(const Vector& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

inline Vector Vector::operator-(const float f) const
{
	return Vector(x - f, y - f, z - f);
}

inline Vector Vector::operator/(const float f) const
{
	return Vector(x / (f + epsilon), y / (f + epsilon), z / (f + epsilon));
}

inline Vector& Vector::operator/=(const float f)
{
	x /= f + epsilon;
	y /= f + epsilon;
	z /= f + epsilon;

	return *this;
}

inline Vector Vector::operator*(const float f) const
{
	return Vector(x * f, y * f, z * f);
}

inline Vector& Vector::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

inline Vector Vector::operator*(const Vector& vec) const
{
	return Vector(x * vec.x, y * vec.y, z * vec.z);
}

inline Vector Vector::operator+(const Vector& vec) const
{
	return Vector(x + vec.x, y + vec.y, z + vec.z);
}

inline Vector& Vector::operator+=(const Vector& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

inline Vector Vector::operator+(const float f) const
{
	return Vector(x + f, y + f, z + f);
}

inline bool Vector::operator==(const Vector& vec) const
{
	return vec.x == x && vec.y == y && vec.z == z;
}

inline void Vector::Init(const float x, const float y, const float z)
{
	this->x = x;
	this->x = y;
	this->z = y;
}

inline bool Vector::IsZero() const
{
	return (x == 0.f && y == 0.f && z == 0.f);
}

inline float Vector::Length() const
{
	return std::sqrt((x * x) + (y * y) + (z * z));
}

inline float Vector::Length2D() const
{
	return std::sqrt((x * x) + (y * y));
}

inline float Vector::LengthSqr() const
{
	return ((x * x) + (y * y) + (z * z));
}

inline float Vector::Length2DSqr() const
{
	return ((x * x) + (y * y));
}

inline float Vector::Distance(const Vector& vec) const
{
	return (*this - vec).Length();
}

inline float Vector::Distance2D(const Vector& vec) const
{
	return (*this - vec).Length2D();
}

inline float Vector::Distance2DSqr(const Vector& vec) const
{
	return (*this - vec).Length2DSqr();
}

inline Vector Vector::Cross(const Vector& vec) const
{
	return (*this) * (vec);
}

inline float Vector::Dot(const Vector& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

inline float Vector::Normalize()
{
	float l = Length();
	float m = 1.0f / (l + epsilon);

	x *= m;
	y *= m;
	z *= m;

	return l;
}

inline float VectorNormalize(Vector& v)
{
	float l = v.Length();

	v /= l;

	return l;
}

inline float Vector::NormalizeInPlace()
{
	return VectorNormalize(*this);
}

void inline SinCos(float radians, float& sine, float& cosine)
{
	sine = std::sin(radians);
	cosine = std::cos(radians);
}

inline float Rad2Deg(float rad)
{
	return rad * (180.f / pi);
}

inline float Deg2Rad(float deg)
{
	return deg * (pi / 180.f);
}

inline void MatrixSetColumn(const Vector& in, int column, VMatrix& out)
{
	out[0][column] = in.x;
	out[1][column] = in.y;
	out[2][column] = in.z;
}

inline void AngleMatrix(const Angle& angles, VMatrix& matrix)
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(Deg2Rad(angles.p), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);
	SinCos(Deg2Rad(angles.r), sr, cr);

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = sp * crcy + srsy;
	matrix[1][2] = sp * crsy - srcy;
	matrix[2][2] = cr * cp;

	MatrixSetColumn(Vector(0, 0, 0), 3, matrix);
}

inline void AngleMatrix(const Angle& angle, const Vector& origin, VMatrix& matrix)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(Deg2Rad(angle.y), sy, cy);
	SinCos(Deg2Rad(angle.p), sp, cp);
	SinCos(Deg2Rad(angle.r), sr, cr);

	// matrix = (YAW * PITCH) * ROLL
	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = (sp * crcy + srsy);
	matrix[1][2] = (sp * crsy - srcy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = origin[0];
	matrix[1][3] = origin[1];
	matrix[2][3] = origin[2];
}

inline void AngleVectors(const Angle& angles, Vector& forward)
{
	float sp, sy, cp, cy;

	SinCos(Deg2Rad(angles.p), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
	forward.Normalize();
}

inline void AngleVectors(const Angle& angles, Vector& forward, Vector& right, Vector& up)
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(Deg2Rad(angles.p), sp, cp);
	SinCos(Deg2Rad(angles.y), sy, cy);
	SinCos(Deg2Rad(angles.r), sr, cr);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
	forward.Normalize();

	right.x = -(sr * sp * cy) + (cr * sy);
	right.y = -(sr * sp * sy) + -(cr * cy);
	right.z = -(sr * cp);
	right.Normalize();

	up.x = cr * sp * cy + -sr * -sy;
	up.y = cr * sp * sy + -sr * cy;
	up.z = cr * cp;
	up.Normalize();
}

inline void VectorRotate(const Vector& in, const VMatrix& matrix, Vector& out)
{
	out.x = in.Dot(Vector(matrix[0][0], matrix[0][1], matrix[0][2]));
	out.y = in.Dot(Vector(matrix[1][0], matrix[1][1], matrix[1][2]));
	out.z = in.Dot(Vector(matrix[2][0], matrix[2][1], matrix[2][2]));
}

inline void VectorRotate3x4(Vector in, VMatrix& matrix, Vector& out)
{
	out.x = in.Dot(Vector(matrix[0][0], matrix[0][1], matrix[0][2])) + matrix[0][3];
	out.y = in.Dot(Vector(matrix[1][0], matrix[1][1], matrix[1][2])) + matrix[1][3];
	out.z = in.Dot(Vector(matrix[2][0], matrix[2][1], matrix[2][2])) + matrix[2][3];
}

inline void VectorTransform(const Vector& in, const VMatrix& matrix, Vector& out)
{
	VectorRotate(in, matrix, out);

	out.x += matrix[0][3];
	out.y += matrix[1][3];
	out.z += matrix[2][3];
}

inline void VectorRotate(const Vector& vec, const Angle& ang, Vector& out)
{
	VMatrix matrix;

	AngleMatrix(ang, matrix);
	VectorRotate(vec, matrix, out);
}

inline Vector Vector::Rotate(const Angle& angles) const
{
	Vector out;
	VectorRotate(*this, angles, out);

	return out;
}

inline void VectorAngles(const Vector& vec, Angle& angles)
{
	angles.p = Rad2Deg(atan2(-vec.z, vec.Length2D()));
	angles.y = Rad2Deg(atan2(vec.y, vec.x));
}

inline float CalculateFOV(const Angle& viewang, const Angle& aimang)
{
	//Vector ang, aim, r, u;

	//AngleVectors(viewang, aim, r, u);
	//AngleVectors(aimang, ang, r, u);

	//return Rad2Deg(acos(aim.Dot(ang) / (aim.Dot(aim))));

	return abs(normalize(viewang.p - aimang.p)) + abs(normalize(viewang.y - aimang.y));
}
