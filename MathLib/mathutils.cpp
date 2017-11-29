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

//float clamp(const float &v, float max, float min)
//{
//	if (v > max)
//	{
//		return max;
//	}
//	else if (v < min)
//	{
//		return min;
//	}
//	else
//	{
//		return v;
//	}
//}
//
//int clamp(const int &v, int max, int min)
//{
//	if (v > max)
//	{
//		return max;
//	}
//	else if (v < min)
//	{
//		return min;
//	}
//	else
//	{
//		return v;
//	}
//}
