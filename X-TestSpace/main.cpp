#include <iostream>

#include "mathutils.h"
#include "vec2.h"

void printVec2(vec2 vec);

int main() 
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

	getchar();
	return 0;
}

void printVec2(vec2 vec)
{
	std::cout << "x: " << vec.x << " y: " << vec.y << std::endl;
}
