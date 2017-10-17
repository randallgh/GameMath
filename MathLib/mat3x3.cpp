#include "mat3x3.h"
#include <cmath>

vec3 & mat3x3::operator[](size_t idx)
{
	//vec3 retval = {};
	//int index = 0;
	//for (int i = 0 + (idx * 3); i < 3 + (idx * 3); ++i)
	//{
	//	retval[index] = m[i];
	//	++index;
	//}
	//return retval;

	return c[idx];
}

const vec3 & mat3x3::operator[](size_t idx) const
{
	//vec3 retval = {};
	//int index = 0;
	//for (int i = 0 + (idx * 3); i < 3 + ( idx * 3); ++i)
	//{
	//	retval[index] = m[i];
	//	++index;
	//}
	//return retval;

	return c[idx];
}

bool operator==(const mat3x3 & A, const mat3x3 & B)
{
	for (int i = 0; i < 9; ++i)
	{
		if(A.m[i] != B.m[i])
		{
			return false;
		}
	}
	
	return true;
}

bool operator!=(const mat3x3 & A, const mat3x3 & B)
{
	for (int i = 0; i < 9; ++i)
	{
		if (A.m[i] != B.m[i])
		{
			return true;
		}
	}

	return false;
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
	const mat3x3 aT = transpose(A);
	mat3x3 retval = mat3x3::zero();

	for (int b_i = 0; b_i < 3; ++b_i)
	{
		for (int a_i = 0; a_i < 3; ++a_i)	
		{
			retval.mm[b_i][a_i] = dot(aT[a_i], B[b_i]);
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

mat3x3 translate(const vec2 & t)
{
	return mat3x3{ 1,0,0,
				   0,1,0,
				   t.x,t.y,1 };
}

mat3x3 scale(const vec2 & s)
{
	return mat3x3{ s.x,0,0,
				   0,s.y,0,
				   0,0,1 };
}

mat3x3 rotate(float deg)
{
	float rad = deg * 0.0174533;

	return mat3x3{ cosf(rad),  sinf(rad),  0,
				   -sinf(rad), cosf(rad),  0,
				   0,         0,         1 };
}
