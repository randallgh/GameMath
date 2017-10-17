#include "mat3x3.h"

vec3 & mat3x3::operator[](size_t idx)
{
	vec3 retval = {};
	int index = 0;
	for (int i = 0 + (idx * 3); i < 3 + (idx * 3); ++i)
	{
		retval[index] = m[i];
		++index;
	}
	return retval;
}

const vec3 & mat3x3::operator[](size_t idx) const
{
	vec3 retval = {};
	int index = 0;
	for (int i = 0 + (idx * 3); i < 3 + ( idx * 3); ++i)
	{
		retval[index] = m[i];
		++index;
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
	mat3x3 retval = mat3x3::zero();
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			for (int index = 0; index < 3; ++index)
			{
				retval.m[row + (col * 3)] += A.m[row + (index * 3)] * B.m[index + (col * 3)];
			}
		}
	}
	return retval;
}

vec3 operator*(const mat3x3 & A, const vec3 & B)
{
	mat3x3 retval = transpose(A);

	return vec3{ dot(retval[0], B), 
				 dot(retval[1], B), 
				 dot(retval[2], B) 
	};
}

mat3x3 transpose(const mat3x3 & A)
{
	return mat3x3{  A.m[0], A.m[3], A.m[6],
					A.m[1], A.m[4], A.m[7],
					A.m[2], A.m[5], A.m[8]
	};
}

float determinant(const mat3x3 & A)
{
	return dot(A[0], cross(A[1], A[2]));
}

mat3x3 inverse(const mat3x3 & A)
{
	float di = 1 / determinant(A);
	return transpose( 
		mat3x3 { 
			cross(A[1],A[2])*di,
			cross(A[2],A[0])*di,
			cross(A[0],A[1])*di,
		}
	);
}