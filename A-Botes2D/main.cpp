#include "Transform.h"
#include "Collider.h"

#include "sfwdraw.h"
#include "Screen.h"

//Ship
#include "Ship.h"
#include "Hull.h"

#include <iostream>

bool up;
bool down;
bool left;
bool right;

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

	akizukiHull[1]->transform->position = { 15,0 };
	akizukiHull[1]->radius = 30;

	akizukiHull[2]->transform->position = { -15,0 };
	akizukiHull[2]->radius = 30;

	Ship Akizuki(akizukiHull, 3);
	Akizuki.transform->dimension = { 1,1 };
	Akizuki.transform->position = { 400, 300 };
	Akizuki.horsepower = 50000;
	Akizuki.collider->mass = 3700;

	/*for (int i = 0; i < 3; ++i)
	{
		akizukiHull[i]->transform->e_parent = Akizuki.transform;
	}*/

	while (sfw::stepContext())
	{
		float t = sfw::getDeltaTime();

		up = sfw::getKey(KEY_UP);
		down = sfw::getKey(KEY_DOWN);
		left = sfw::getKey(KEY_LEFT);
		right = sfw::getKey(KEY_RIGHT);

		if (up) {
			Akizuki.enginePower += 0.25f;
		}
		else if (down) {
			Akizuki.enginePower -= 0.25f;
		}
		else if (left) {
			Akizuki.transform->angle += 1;
		}
		else if (right) {
			Akizuki.transform->angle -= 1;
		}

		Akizuki.update();
		Akizuki.draw();

	}

	sfw::termContext();
	return 0;
}