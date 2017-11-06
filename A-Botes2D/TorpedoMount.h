#pragma once
#include "GameObject.h"
#include "vec2.h"
#include "mat3x3.h"

class Ship;
class Torpedo;
class Physics;

class TorpedoMount : public GameObject
{
public:
	TorpedoMount();
	~TorpedoMount();

	Ship * parentShip;
	Torpedo * torpedo;
	Physics * physics;

	float reloadTime;
	float reloadTimer;

	int MAX_TORPEDOES = 20;
	int numTorpedoes = 0;
	Torpedo ** torpedos = new Torpedo*[MAX_TORPEDOES];

	void update(float dt);
	void draw(mat3x3 cam);

	void launchNext(vec2 pos);
	void launchAll(vec2 pos);
};

