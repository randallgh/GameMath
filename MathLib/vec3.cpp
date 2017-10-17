#include "vec3.h"

#include <cmath>
#include <cfloat>

float & vec3::operator[](int index)
{
	return v[index];
}

float vec3::operator[](int index) const
{
	return v[index];
}

vec3 operator+(const vec3 & lhs, const vec3 & rhs)
{
	vec3 retval = { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	return retval;
}

vec3 operator-(const vec3 & lhs, const vec3 & rhs)
{
	vec3 retval = { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	return retval;
}

vec3 operator*(const vec3 & lhs, const float & rhs)
{
	vec3 retval = { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
	return retval;
}

vec3 operator*(const float & lhs, const vec3 & rhs)
{
	vec3 retval = { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
	return retval;
}

vec3 operator/(const vec3 & lhs, const float & rhs)
{
	vec3 retval = { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
	return retval;
}

vec3 operator-(const vec3 & lhs)
{
	vec3 retval = { -lhs.x, -lhs.y, -lhs.z };
	return retval;
}

vec3 & operator+=(vec3 & lhs, const vec3 & rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

vec3 & operator-=(vec3 & lhs, const vec3 & rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

vec3 & operator*=(vec3 & lhs, const float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

vec3 & operator/=(vec3 & lhs, const float rhs)
{
	lhs = lhs / rhs;
	return lhs;
}

bool operator==(const vec3 & lhs, const vec3 & rhs)
{
	if(abs(lhs.x - rhs.x) < FLT_EPSILON &&
		abs(lhs.y - rhs.y) < FLT_EPSILON &&
		abs(lhs.z - rhs.z) < FLT_EPSILON)
	{
		return true;
	}
	return false;
}

bool operator!=(const vec3 & lhs, const vec3 & rhs)
{
	if (abs(lhs.x - rhs.x) < FLT_EPSILON &&
		abs(lhs.y - rhs.y) < FLT_EPSILON &&
		abs(lhs.z - rhs.z) < FLT_EPSILON)
	{
		return false;
	}
	return true;
}

vec3 min(vec3 a, vec3 b)
{
	return magnitude(a) < magnitude(b) ? a : b;
}

vec3 max(vec3 a, vec3 b)
{
	return magnitude(a) > magnitude(b) ? a : b;
}

float magnitude(const vec3 v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

vec3 normal(const vec3 v)
{
	vec3 retval = v / magnitude(v);
	return retval;
}

vec3 normalize(vec3 & v)
{
	v /= magnitude(v);
	return v;
}

float dot(const vec3 & v1, const vec3 & v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float distance(vec3 & v1, vec3 & v2)
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v2.y, 2) + pow(v2.z - v2.z, 2));
}

vec3 &clamp(vec3 & v, const vec3 & min, const vec3 & max)
{
	for (int i = 0; i < 3; ++i)
	{
		if (v[i] >= max[i])
		{
			v[i] = max[i];
		}
		if (v[i] <= min[i])
		{
			v[i] = min[i];
		}
	}
	
	return v;
}

vec3 cross(const vec3 & v, const vec3 & w)
{
	return vec3{
		(v.y * w.z) - (v.z * w.y),
		-((v.x * w.z) - (v.z * w.x)),
		(v.x * w.y) - (v.y * w.x)
	};
}
