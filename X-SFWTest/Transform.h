#pragma once

#include "vec2.h"
#include "mat3x3.h"

class Transform
{
public:
	Transform();
	~Transform();

	vec2 position;
	vec2 dimension;
	float angle;

	mat3x3 GetLocalTransform() const;

private:

};

void DrawMatrix(const mat3x3 &t, float drawing_scale);