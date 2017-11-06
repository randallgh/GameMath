#pragma once
#include "GameObject.h"
#include "vec2.h"
#include "mat3x3.h"

class Physics;
class Hull;
class Camera;
class NavalBattery;

class Torpedo;
class TorpedoMount;

class Ship : public GameObject
{
public:
	Ship();
	Ship(std::string t, std::string n, Physics * phys, 
		Hull ** h, int hc, 
		NavalBattery ** mG, int mGC, 
		TorpedoMount ** tM, int tMC);
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
	TorpedoMount ** torpedoMounts;
	int TORPEDO_MOUNT_COUNT;
	
	//Engine
	float enginePower;
	float horsepower;

	void setup(std::string t, std::string n, Physics * phys, Hull ** h, int hc, NavalBattery ** mG, int mGC);

	//Debug to see the lines from the ships guns to a point
	//void drawGunLines(vec2 point, mat3x3 cam);

	/*
	for (int i = 0; i < Akizuki->MAIN_GUNS_COUNT; ++i)
	{
		drawVecLine(
			(mainCam->mat * Akizuki->mainGuns[i]->transform->GetGlobalTransform()).c[2].xy,
			(mousePos.GetGlobalTransform()).c[2].xy, RED);
	}
	*/
	
	//Fires all guns at vec2 pos
	void shootAllGuns(vec2 pos);

	//To be implemented
	//void shootOneGun(vec2 pos);

	//Fire all torpedo mounts at vec2 Pos
	void launchAllTorpedoes(vec2 pos);

	//Fire a single torpedo mount at vec2 Pos
	//void launchOneTorpedoMount(vec2 pos);

	void setWeaponsAngle(vec2 pos);


	void update(float dt);
	void draw();
};

