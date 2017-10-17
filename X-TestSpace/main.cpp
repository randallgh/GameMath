#include <iostream>
#include <cassert>

#include "mathutils.h"
#include "vec2.h"
#include "vec3.h"
#include "mat3x3.h"

void printVec2(vec2 vec);
void printVec3(vec3 vec);

void printMat3(mat3x3 &A)
{
	for (int i = 0; i < 3; ++i)
	{
		std::cout << A.m[i * 3] << A.m[(i * 3) + 1] << A.m[(i * 3) + 2] << std::endl;
	}
}

int main() 
{
	//vector2s();
	//vector3s();

	mat3x3 test = mat3x3::identity();
	printMat3(test);

	printMat3(test * test);

	printVec3(test[0]);
	printVec3(test[1]);
	printVec3(test[2]);

	mat3x3 A = translate(vec2{1,0});
	printMat3(A);
	printMat3(A * inverse(A));
	assert((A * inverse(A)) == test);

	mat3x3 Z = mat3x3::zero();
	mat3x3 I = mat3x3::identity();
	vec3 v = { 1,2,3 };

	assert(I + Z == I);
	assert(Z + I == I);
	assert(I - Z == I);
	assert(!(Z - I == I));
	assert(transpose (I) == I);
	assert(I*A == A);
	assert(A*I == A);	
	assert(I*v == v);


	mat3x3 T = scale(vec2{ 1,2 })*
			   rotate(90)*
			   translate(vec2{ 3,0 });

	assert((T[2].xy == vec2{ 0,6 }));


	getchar();
	return 0;
}

void vector3s()
{
	
	{
		vec3 v1 = { 0,0,0 };
		vec3 v2 = { 1,0,0 };
		assert(v1 != v2);
	};

	{
		vec3 v1 = { 0,0,0 };
		vec3 v2 = { 1,1,1 };
		assert((v1 += v2) == v2);
	};

	{
		vec3 v1 = { 0,0,0 };
		vec3 v2 = { 1,1,1 };
		assert(min(v1, v2) == v1);
	};

	{
		vec3 v1 = { 0,0,0 };
		vec3 v2 = { 1,1,1 };
		assert(max(v1, v2) == v2);
	};

	{
		vec3 v1 = { 0,0,0 };
		vec3 v2 = { 1,1,1 };
		for (int i = 0; i < 200; ++i)
		{
			v1 *= i;
			v2 *= i;
			assert(min(v1, v2) == v1);
		}
	};

	{
		vec3 v1 = { 0,0,0 };
		vec3 v2 = { 1,1,1 };

		v1[0] = 1;
		v1[1] = 1;
		v1[2] = 1;

		assert(v1 == v2);
	}

}

void vector2s()
{
	std::cout << min(9, 0) << std::endl;
	std::cout << max(9, 0) << std::endl;

	vec2 vecA = { 1,2 };
	vec2 vecB = { 5,4 };

	vec2 vecC = vecA + vecB;
	vec2 vecD = vecB - vecA;

	printVec2(vecC);
	printVec2(vecD);

	vec2 vecE = vecA * 2;
	vec2 vecF = 2 * vecB;

	printVec2(vecE);
	printVec2(vecF);

	printVec2(vecE / 2);
	printVec2(-vecE);

	vec2 vecZ = { 0,0 };
	vecZ += vecA;
	vecZ += vecA;
	printVec2(vecZ);

	vecZ -= vecA;
	printVec2(vecZ);

	std::cout << vecZ[0] << std::endl;
}

void printVec2(vec2 vec)
{
	std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;
}

void printVec3(vec3 vec)
{
	std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << std::endl;
}
