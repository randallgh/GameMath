#pragma once
#include "GameObject.h"
#include "vec2.h"


class Ship;
class Shell;
class Physics;

class NavalBattery : public GameObject
{
public:
	NavalBattery(Physics * phys, vec2 pos, float reload);
	~NavalBattery();

	float reloadTime;
	float reloadTimer;

	void update();
	void draw();

	void shoot(vec2 pos);

	Shell ** shells = new Shell*[MAX_SHELLS];
	int MAX_SHELLS = 20;
	int numShells = 0;

	Ship * parentShip;
	Shell * shellType1;
	Physics * physics;

private:
	Shell* findNextShell();
};

