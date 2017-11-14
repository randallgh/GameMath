#pragma once
#include "GameObject.h"

class Ship;
class Physics;

class Shell : public GameObject
{
public:
	Shell();
	~Shell();

	float damage;
	float speed;

	float life;
	float maxLife;

	float distanceTraveled;
	float maxDistance;

	//float radius
	Ship * parentShip;

	/*
	t   | tag
	n   | name
	spe | speed
	lif | life
	dam | damage
	mDis | max distance
	*/
	void setupShell(Physics * phys, std::string t, std::string n, float r, float spe, float lif, float dam, int mDis);
	/*
	s   | Shell you would like to copy parms from
	*/
	void setupShell(const Shell &s, Physics * phys);
	/*
	s   | Shell you would like to copy parms from
	*/
	void setupShell(const Shell *s, Physics * phys);
	void reset();

	void update(float dt);
	void draw();
};

