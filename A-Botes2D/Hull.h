#pragma once
#include "GameObject.h"
#include "mat3x3.h"

struct SATGeometry;
class Physics;
class Ship;

class Hull : public GameObject
{
public:
	Hull(Physics * phys);
	Hull(SATGeometry &geo, Physics * phys);
	~Hull();

	//Rendering
	//int radius;
	unsigned color;

	Ship * parentShip;


	//Game Stats
	//int health;

	void update();
	void draw(mat3x3 cam);
};

