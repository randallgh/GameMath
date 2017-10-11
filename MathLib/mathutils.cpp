#include "mathutils.h"
#include "vec2.h"
#include <cmath>

float min(float a, float b)
{
	return a < b ? a : b;
}

float max(float a, float b)
{
	return a > b ? a : b;
}

float magnitude(const vec2 v)
{
	return sqrt(pow(v.x,2) + pow(v.y,2));
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
