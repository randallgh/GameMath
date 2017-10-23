#pragma once
#include "GameObject.h"


static enum ColliderType
{
	Circle
};


//Whenever a collider is constructed it must be added to the physics array
class Collider
{
public:
	Collider();
	~Collider();

	void update();
	void draw();

	ColliderType type;

	GameObject * gameObject;

	int radius;
	float mass;

private:

};