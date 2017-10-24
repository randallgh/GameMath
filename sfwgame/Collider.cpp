#include "Collider.h"
#include "Transform.h"
#include "sfwdraw.h"
#include "Physics.h"

Collider::Collider(GameObject * go, Physics * phys)
{
	type = ColliderType::Circle;
	int radius = 0;
	float mass = 1;

	gameObject = go;

	vec2 acceleration = {0,0};
	vec2 velocity = {0,0};

	phys->addCollider(this);
}

Collider::~Collider()
{
}

void Collider::update()
{
	if (this == nullptr) { return; }
	if (!gameObject->isEnabled) { return; }
	gameObject->transform->position += velocity * sfw::getDeltaTime();
}

void Collider::draw()
{

}
