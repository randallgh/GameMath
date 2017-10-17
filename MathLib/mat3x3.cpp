#include "mat3x3.h"

vec3 & mat3x3::operator[](size_t idx)
{
	vec3 retval = {};
	switch (idx)
	{
	case 0:
		for (int i = 0; i < 3; ++i)
		{
			retval[i] = m[i];
		}
		break;
	case 1:
		for (int i = 3; i < 6; ++i)
		{
			retval[i] = m[i];
		}
		break;
	case 2:
		for (int i = 6; i < 9; ++i)
		{
			retval[i] = m[i];
		}
		break;
	default:
		break;
	}
	return retval;
}

const vec3 & mat3x3::operator[](size_t idx) const
{
	// TODO: insert return statement here
	vec3 retval = {};
	switch (idx)
	{
	case 0:
		for (int i = 0; i < 3; ++i)
		{
			retval[i] = m[i];
		}
		break;
	case 1:
		for (int i = 3; i < 6; ++i)
		{
			retval[i] = m[i];
		}
		break;
	case 2:
		for (int i = 6; i < 9; ++i)
		{
			retval[i] = m[i];
		}
		break;
	default:
		break;
	}
	return retval;
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
	mat3x3 retval = {};
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			for (int index = 0; index < 3; ++index)
			{
				retval.m[row + (col * 3)] += A.m[row + (index * 3)] * B.m[index];
			}
		}
	}
	return retval;
}

mat3x3 operator*(const mat3x3 & A, const vec3 & V)
{
	return mat3x3();
}