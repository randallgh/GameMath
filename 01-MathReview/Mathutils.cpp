#include "Mathutils.h"
#include <cmath>
float pi = 3.14;

float dbl(float v)
{
	return v * 2;
}

float sqr(float v)
{
	return v * v;
}

float cube(float v)
{
	return v * v * v;
}

float degToRad(float deg)
{
	return deg * pi / 180;
}

float radToDeg(float rad)
{
	return rad * 180 / pi;
}

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt( sqr(x2 - x1) + sqr(y2 - y1) );
}

float cubicBezier(float time, float p1, float p2, float p3, float p4)
{
	return pow(1 - time, 3) * p1 + 3 * pow(1 - time, 2)*time*p2 + 3 * pow(1 - time, 2)*p3 + pow(time, 3) * p4;
}
