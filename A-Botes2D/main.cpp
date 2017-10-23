#include "Transform.h"
#include "Collider.h"

#include "sfwdraw.h"
#include "Screen.h"

//Ship
#include "Ship.h"
#include "Hull.h"

#include <iostream>

int main()
{
	ScreenInfo SCR_INFO;
	sfw::initContext(SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT, SCR_INFO.SCR_NAME);

	Hull ** akizukiHull = new Hull*[3];
	for (int i = 0; i < 3; ++i) 
	{
		akizukiHull[i] = new Hull();
		akizukiHull[i]->transform->dimension = { 1,1 };
	}

	akizukiHull[0]->radius = 30;

	akizukiHull[1]->transform->position = { 0,15 };
	akizukiHull[1]->radius = 30;

	akizukiHull[2]->transform->position = { 0,-15 };
	akizukiHull[2]->radius = 30;

	Ship Akizuki(akizukiHull, 3);
	Akizuki.transform->dimension = { 1,1 };
	Akizuki.transform->position = { 400, 300 };
	Akizuki.enginePower = 50000;
	Akizuki.collider->mass = 3700;

	/*for (int i = 0; i < 3; ++i)
	{
		akizukiHull[i]->transform->e_parent = Akizuki.transform;
	}*/

	while (sfw::stepContext())
	{
		float t = sfw::getDeltaTime();

		bool up = sfw::getKey(KEY_UP);
		bool down = sfw::getKey(KEY_DOWN);
		bool left = sfw::getKey(KEY_LEFT);
		bool right = sfw::getKey(KEY_RIGHT);


		if (up) {

		}
		else if (down) {
		}
		else if (left) {
		}
		else if (right) {
		}
		else {
			Akizuki.collider->velocity = { 0,0 };
		}

		Akizuki.update();
		Akizuki.draw();

	}

	sfw::termContext();
	return 0;
}