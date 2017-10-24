#pragma once
#include "GameObject.h"
#include "vec2.h"


class Ship;

class NavalBattery : public GameObject
{
public:
	NavalBattery(vec2 pos);
	~NavalBattery();

	void update();
	void draw();

	Ship * parentShip;
};

