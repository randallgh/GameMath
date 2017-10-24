#include "Camera.h"
#include "Transform.h"

Camera::Camera(float w, float h)
{
	screenWidth = w;
	screenHeight = h;
}


Camera::~Camera()
{

}

void Camera::SetupMatrix(Transform * t)
{
	vec2 target = t->GetGlobalTransform().c[2].xy;
	mat3x3 proj = translate({ (float)screenWidth / 2, (float)screenHeight / 2 }) * scale({ 1,1 });
	mat3x3 view = inverse(translate(target));
	this->mat = proj * view;
}
