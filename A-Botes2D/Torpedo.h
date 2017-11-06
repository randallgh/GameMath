#pragma once
#include "GameObject.h"
#include "mat3x3.h"

class TorpedoMount;

class Torpedo : public GameObject
{
public:
	Torpedo();
	~Torpedo();

	//Parent
	TorpedoMount * parentMount;

	//Varibles
	float length;
	float width;

	float life;
	float maxLife;

	float distanceTraveled;
	float maxDistance;

	//Feet / Second 
	float speed;
	//Feet
	float range;

	//Methods

	void reset();

	void update(float dt);
	void draw(mat3x3 cam);
};

