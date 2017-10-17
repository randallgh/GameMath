#include "mat3x3.h"

vec3 & mat3x3::operator[](size_t idx)
{
	vec3 retval = {};
	switch (idx)
	{
	case 0:
		for (int i = 0; i < 3; ++i)
		{

		}

		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
	return retval;
}

const vec3 & mat3x3::operator[](size_t idx) const
{
	// TODO: insert return statement here
}


mat3x3 operator+(const mat3x3 & A, const mat3x3 & B)
{
	mat3x3 retval;

	for (int i = 0; i < 9; ++i)
	{
		retval.m[i] = A.m[i] + B.m[i];
	}

	return retval;
}

mat3x3 operator-(const mat3x3 & A, const mat3x3 & B)
{
	mat3x3 retval;

	for (int i = 0; i < 9; ++i)
	{
		retval.m[i] = A.m[i] - B.m[i];
	}

	return retval;
}

mat3x3 operator*(const mat3x3 & A, const mat3x3 & B)
{
	return mat3x3();
}

mat3x3 operator*(const mat3x3 & A, const vec3 & V)
{
	return mat3x3();
}