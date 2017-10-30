#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"

Rigidbody::Rigidbody(GameObject * go)
{
	gameObject = go;

	radius = 0;
	mass = 1;
	drag =0.25;

	acceleration = { 0,0 };
	velocity = { 0,0 };
	force = { 0,0 };
	impulse = { 0,0 };

	torque = 0;
	angularAcceleration = 0;
	angularVelocity = 0;
	angularDrag = 0;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::update(float dt)
{
	if (this == nullptr) { return; }
	if (!gameObject->isEnabled) { return; }
	gameObject->transform->position += velocity * dt;
}

void Rigidbody::integrate(Transform & T, float dt)
{
	acceleration = force / mass;
	velocity += acceleration * dt + impulse / mass;
	T.position += velocity * dt;
	impulse = { 0,0 };
	force = -velocity * drag;

	angularAcceleration = torque / mass;
	angularVelocity = angularAcceleration * dt;
	T.angle += angularVelocity * dt;
	torque = -angularVelocity * angularDrag;
}
