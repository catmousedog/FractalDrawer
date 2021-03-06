
#pragma once

#include "Util.h"

struct Vector
{
	double x, y;

	Vector() : x(0), y(0)
	{
	}
	Vector(double x, double y) : x(x), y(y)
	{
	}
	Vector(const Vector& v) : x(v.x), y(v.y)
	{
	}

	bool IsZero() const
	{
		return x == 0 && y == 0;
	}
	double AbsSquared() const
	{
		return x * x + y * y;
	}
	Vector operator-() const
	{
		return Vector(-x, -y);
	}
	Vector operator+(const Vector& v) const
	{
		return Vector(v.x + x, v.y + y);
	}
	Vector operator-(const Vector& v) const
	{
		return Vector(v.x - x, v.y - y);
	}
	double operator*(const Vector& v) const
	{
		return v.x * x + v.y * y;
	}
	Vector operator*(const double a) const
	{
		return Vector(x * a, y * a);
	}
	Vector TermMultiply(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y);
	}
	Vector& operator+=(const Vector& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector& operator-=(const Vector& v)
	{
		*this += (-v);
		return *this;
	}
	std::string string()
	{
		return "v: " + std::to_string(x) + " | " + std::to_string(y);
	}
};

//inline Vector sgn(const Vector& v)
//{
//	return Vector(sgn(v.x), sgn(v.y));
//}