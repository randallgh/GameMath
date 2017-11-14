#include "Camera.h"
#include "Transform.h"
#include "mathutils.h"

Camera::Camera()
{
}

Camera::~Camera()
{

}

void Camera::SetupMatrix(Transform * t)
{
	vec2 target = t->GetGlobalTransform().c[2].xy;
	mat3x3 proj = translate({ (float)screenWidth / 2, (float)screenHeight / 2 }) * scale({ zoom,zoom });
	mat3x3 view = inverse(translate(target));
	this->mat = proj * view;
}

void Camera::setZoom(float a)
{
	zoom = clamp(a,2.0f,0.1f);
}

float Camera::getZoom()
{
	return zoom;
}
