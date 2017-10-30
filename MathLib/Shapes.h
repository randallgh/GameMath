#pragma once
#include "vec2.h"

struct Circle
{
	vec2 position;
	float radius;
};

struct Square
{
	vec2 position;
	float extend;
};

struct Rectangle
{
	vec2 position;
	vec2 extends; //W x H
};