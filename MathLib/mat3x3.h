#pragma once
#include "vec3.h"

union mat3x3
{
	float m[9];
	float mm[3][3];
	vec3 c[3];

	vec3 &operator[](size_t idx);//column accessor
	const vec3 &operator[](size_t idx) const;

	static mat3x3 identity(); //creates and returns a identity matrix
};

mat3x3 operator+(const mat3x3 &A, const mat3x3 &B);
mat3x3 operator-(const mat3x3 &A, const mat3x3 &B);

mat3x3 operator*(const mat3x3 &A, const mat3x3 &B);//Combine Transformations
mat3x3 operator*(const mat3x3 &A, const vec3 &V);  //Apply a transformation

mat3x3 transpose(const mat3x3 &A); //flips the rows and columns

//Unknown
float determinant(const mat3x3 &A);
mat3x3 inverse(const mat3x3 &A);