#pragma once

float min(float a, float b);
float max(float a, float b);


//float clamp(const float &v, float max, float min);
//int clamp(const int &v, int max, int min);

template<typename T>
inline T clamp(const T & v, T max, T min)
{
	if (v > max)
	{
		return max;
	}
	else if (v < min)
	{
		return min;
	}
	else
	{
		return v;
	}
}

#define EPSILON 0.0001
#define Deg2Rad 0.0174533
#define Rad2Deg 57.2958
#define PI 3.14159265
