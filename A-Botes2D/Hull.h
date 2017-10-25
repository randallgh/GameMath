#pragma once
#include "GameObject.h"

class Physics;
class Ship;

class Hull : public GameObject
{
public:
	Hull(Physics * phys);
	~Hull();

	//Rendering
	//int radius;
	unsigned color;

	Ship * parentShip;


	//Game Stats
	//int health;

	void update();
	void draw();
};

