#pragma once
#include "GameObject.h"


class Hull : public GameObject
{
public:
	Hull();
	~Hull();

	//Rendering
	int radius;
	unsigned color;


	//Game Stats
	//int health;

	void update();
	void draw();
};

