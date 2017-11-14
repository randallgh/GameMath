#pragma once
#include "GameObject.h"
#include "mat3x3.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	float screenWidth; 
	float screenHeight;

	mat3x3 mat;
	void SetupMatrix(Transform * t);
	void setZoom(float a);
	float getZoom();
private:
	float zoom = 1;
};

