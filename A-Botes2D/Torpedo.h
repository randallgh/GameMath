#pragma once
#include "GameObject.h"
#include "mat3x3.h"

class TorpedoMount;
class Physics;

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


	/*
	n | name
	w | width
	h | height
	s | speed
	l | life
	dam  | damage
	mDis | maxDistance
	*/
	void setup(Physics * phys, std::string n, float w, float h, float s,
		float l, float dam, float mDis);

	void setup(Physics * phys, const Torpedo &torp);
	void setup(Physics * phys, const Torpedo *torp);

	void reset();

	void update(float dt);
	void draw(mat3x3 cam);
};

