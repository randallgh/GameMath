#pragma once
#include "vec3.h"

union mat3x3
{
	vec3 c[3];
	float m[9];
	float mm[3][3];

	vec3 &operator[](size_t idx);//column accessor
	const vec3 &operator[](size_t idx) const;

	static mat3x3 identity() //creates and returns a identity matrix
	{
		return mat3x3{ 1,0,0, 
					   0,1,0, 
					   0,0,1 };
	}

	static mat3x3 zero() //creates and returns a zero matrix
	{
		return mat3x3{ 0,0,0,
					   0,0,0,
					   0,0,0 };
	}
};

mat3x3 operator+(const mat3x3 &A, const mat3x3 &B);
mat3x3 operator-(const mat3x3 &A, const mat3x3 &B);

mat3x3 operator*(const mat3x3 &A, const mat3x3 &B);//Combine Transformations
vec3 operator*(const mat3x3 &A, const vec3 &B);  //Apply a transformation

mat3x3 transpose(const mat3x3 &A); //flips the rows and columns

//Unknown
float determinant(const mat3x3 &A);
mat3x3 inverse(const mat3x3 &A);