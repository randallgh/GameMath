#pragma once
#include "vec2.h"

class GameObject;
class Transform;

class Rigidbody
{
public:
	Rigidbody(GameObject * go);
	~Rigidbody();

	int radius;
	float mass, drag;

	int elasticity;

	vec2 acceleration,
		velocity,
		force,
		impulse;

	float angularVelocity,
		  angularAcceleration,
		  torque;

	float angularDrag;



	GameObject * gameObject;

	void update(float dt);

	void integrate(Transform &T, float dt);
};

