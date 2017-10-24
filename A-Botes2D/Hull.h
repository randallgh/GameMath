#pragma once
#include "GameObject.h"

class Physics;

class Hull : public GameObject
{
public:
	Hull(Physics * phys);
	~Hull();

	//Rendering
	int radius;
	unsigned color;


	//Game Stats
	//int health;

	void update();
	void draw();
};

