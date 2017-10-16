#include "vec2.h"

#include <cmath>
#include <cfloat>

vec2 operator+(const vec2 & lhs, const vec2 & rhs)
{
	vec2 retval = { lhs.x + rhs.x, lhs.y + rhs.y };
	return retval;
}

vec2 operator-(const vec2 & lhs, const vec2 & rhs)
{
	vec2 retval = { lhs.x - rhs.x, lhs.y - rhs.y };
	return retval;
}

vec2 operator*(const vec2 & lhs, const float & rhs)
{
	vec2 retval = { lhs.x * rhs, lhs.y * rhs };
	return retval;
}

vec2 operator*(const float & lhs, const vec2 & rhs)
{
	vec2 retval = { lhs * rhs.x, lhs * rhs.y };
	return retval;
}

vec2 operator/(const vec2 & lhs, const float & rhs)
{
	vec2 retval = { lhs.x / rhs,lhs.y / rhs };
	return retval;
}

vec2 operator-(const vec2 & rhs)
{
	vec2 retval = { -rhs.x,-rhs.y };
	return retval;
}

vec2 & operator+=(vec2 & lhs, const vec2 & rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

vec2 & operator-=(vec2 & lhs, const vec2 & rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

vec2 & operator*=(vec2 & lhs, const float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

vec2 & operator/=(vec2 & lhs, const float rhs)
{
	lhs = lhs / rhs;
	return lhs;
}

bool operator==(const vec2 & lhs, const vec2 & rhs)
{
	// this isn't quite right, but game engines tend
	// to do something fairly close to this process
	//
	// floating-point math is weird! check this out!
	// http://floating-point-gui.de/errors/comparison/

	const int qty = (sizeof(lhs.v) / sizeof(lhs.v[0]));
	for (int i = 0; i < qty; ++i)
	{
		// is the discrepancy within acceptable limits?
		if (std::abs(lhs.v[i] - rhs.v[i]) < FLT_EPSILON)
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const vec2 & lhs, const vec2 & rhs)
{
	// this isn't quite right, but game engines tend
	// to do something fairly close to this process
	//
	// floating-point math is weird! check this out!
	// http://floating-point-gui.de/errors/comparison/

	const int qty = (sizeof(lhs.v) / sizeof(lhs.v[0]));
	for (int i = 0; i < qty; ++i)
	{
		// is the discrepancy within acceptable limits?
		if (std::abs(lhs.v[i] - rhs.v[i]) < FLT_EPSILON)
		{
			return true;
		}
	}
	return false;
}

float &vec2::operator[](int x)
{
	return  v[x];
}

float vec2::operator[](int x) const
{
	return v[x];
}

//Vec2 Functions

float magnitude(const vec2 v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

vec2 normal(const vec2 v)
{
	vec2 retval = v / magnitude(v);
	return retval;
}

vec2 normalize(vec2 &v)
{
	v /= magnitude(v);
	return vec2();
}

float dot(vec2 &v1, vec2 &v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float distance(vec2 &v1, vec2 &v2)
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v2.y, 2));
}

//vec2 cross(vec2 & v1, vec2 & v2)
//{
//
//	return vec2();
//}

vec2 lerp(vec2 start, vec2 end, float a)
{
	if (a == 0) { return start; }
	else if (a == 1) { return end; }

	vec2 retval = end - start;
	retval *= a;

	return retval;
}

vec2 min(vec2 a, vec2 b)
{
	return magnitude(a) < magnitude(b) ? a : b;
}

vec2 max(vec2 a, vec2 b)
{
	return magnitude(a) > magnitude(b) ? a : b;
}
