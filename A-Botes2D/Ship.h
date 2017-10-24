#pragma once
#include "GameObject.h"
#include "vec2.h"

class Hull;
class Camera;
class NavalBattery;

class Ship : public GameObject
{
public:
	Ship();
	Ship(Hull ** h, int hc, NavalBattery ** mG, int mGC);
	~Ship();

	Camera * cam;
	//Hull
	Hull ** hull;
	int HULL_COUNT;
	//Main Batteries
	NavalBattery ** mainGuns;
	int MAIN_GUNS_COUNT;
	//Secondaries
	NavalBattery ** secondaryGuns;
	int SECONDARY_GUNS_COUNT;
	//Torpedo tubes
	int TORPEDO_MOUNT_COUNT;
	//Engine
	float enginePower;
	float horsepower;

	void shootAllGuns(vec2 pos);
	void setGunAngle(vec2 pos);
	void update();
	void draw();
};

