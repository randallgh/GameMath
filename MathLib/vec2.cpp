#include "vec2.h"

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
