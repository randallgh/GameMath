#pragma once
#include "GameObject.h"

class Hull;

class Ship : public GameObject
{
public:
	Ship();
	Ship(Hull * h, int hc);
	~Ship();

	//Hull
	Hull * hull;
	int HULL_COUNT;
	//Main Batteries
	//Torpedo tubes


	void update();
	void draw();
};

