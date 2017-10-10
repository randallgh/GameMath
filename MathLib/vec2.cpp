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
