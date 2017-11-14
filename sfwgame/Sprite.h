#pragma once
union mat3x3;
#include "sfwdraw.h"

class Sprite
{
public:
	Sprite(const char * path);
	~Sprite();
	void draw(mat3x3 transform, float s = 1.0f, unsigned tint = 0xfffffff, float z = 0.0f);

private:
	unsigned handle;
	float width;
	float height;
};

