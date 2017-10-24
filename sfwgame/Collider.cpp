#include "Collider.h"
#include "Transform.h"
#include "sfwdraw.h"

Collider::Collider(GameObject * go)
{
	type = ColliderType::Circle;
	int radius = 0;
	float mass = 1;

	gameObject = go;

	vec2 acceleration = {0,0};
	vec2 velocity = {0,0};
}

Collider::~Collider()
{
}

void Collider::update()
{
	gameObject->transform->position += velocity * sfw::getDeltaTime();
}

void Collider::draw()
{

}
