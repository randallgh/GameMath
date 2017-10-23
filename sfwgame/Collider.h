#pragma once
#include "GameObject.h"
#include "vec2.h"

static enum ColliderType
{
	Circle
};


//Whenever a collider is constructed it must be added to the physics array
class Collider
{
public:
	Collider(GameObject * go);
	~Collider();

	void update();
	void draw();

	ColliderType type;

	GameObject * gameObject;

	int radius;
	float mass;

	vec2 acceleration;
	vec2 velocity;

private:

};