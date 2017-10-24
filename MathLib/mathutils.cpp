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

float clamp(float &v, float max, float min)
{
	if (v > max) {
		v = max;
		return v;
	}
	else if (v < min) {
		v = min;
		return v;
	}
	else {
		return v;
	}

}
