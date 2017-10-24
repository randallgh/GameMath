#pragma once
#include "GameObject.h"
#include "mat3x3.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	mat3x3 mat;
};

