#pragma once
#include "GameObject.h"
#include "mat3x3.h"

class Camera : public GameObject
{
public:
	Camera(float w, float h);
	~Camera();

	float screenWidth; 
	float screenHeight;

	mat3x3 mat;
	void SetupMatrix(Transform * t);
};

