#pragma once
#include "GameObject.h"
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

	float radius;

	Collider * collider;
	/*
	t   | tag
	n   | name
	spe | speed
	lif | life
	dam | damage
	mDis | max distance
	*/
	void setupShell(std::string t, std::string n, float r, float spe, float lif, float dam, int mDis);
	/*
	s   | Shell you would like to copy parms from
	*/
	void setupShell(const Shell &s);
	/*
	s   | Shell you would like to copy parms from
	*/
	void setupShell(const Shell *s);
	void reset();

	void update();
	void draw();
};

