#pragma once
#include "vec2.h"

class Physics;
class GameObject;

static enum ColliderType
{
	Circle
};


//Whenever a collider is constructed it must be added to the physics array
class Collider
{
public:
	Collider(GameObject * go, Physics * phys);
	~Collider();

	//void update();
	//void draw();

	ColliderType type;

	GameObject * gameObject;

private:

};