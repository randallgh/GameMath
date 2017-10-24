#pragma once
#include "GameObject.h"
class Shell : public GameObject
{
public:
	Shell();
	~Shell();

	int damage;
	float speed;
	float life;
	float maxLife;

	float radius;

	Collider * collider;
};

