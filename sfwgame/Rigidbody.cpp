#include "Rigidbody.h"
#include "GameObject.h"
#include "sfwdraw.h"
#include "Transform.h"

Rigidbody::Rigidbody(GameObject * go)
{
	gameObject = go;

	radius = 0;
	mass = 1;
	acceleration = { 0,0 };
	velocity = { 0,0 };
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::update()
{
	if (this == nullptr) { return; }
	if (!gameObject->isEnabled) { return; }
	gameObject->transform->position += velocity * sfw::getDeltaTime();
}

void Rigidbody::integrate(Transform & T, float dt)
{
	velocity += acceleration * dt;
	T.position += velocity * dt;
}
