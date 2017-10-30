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
	float mass;

	vec2 acceleration,
		velocity,
		force;

	GameObject * gameObject;

	void update();

	void integrate(Transform &T, float dt);
};

