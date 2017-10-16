#include <iostream>
#include <cassert>


#include "mathutils.h"
#include "vec2.h"
#include "vec3.h"

void printVec2(vec2 vec);

int main() 
{
	//vector2s();
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
		assert(min(v1,v2) == v1);
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
			assert(min(v1,v2) == v1);
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

	getchar();
	return 0;
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
