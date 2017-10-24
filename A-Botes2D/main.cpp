#include "sfwdraw.h"
#include "Screen.h"
#include "Camera.h"
#include "Input.h"

#include "Transform.h"
#include "Collider.h"

//Ship
#include "Ship.h"
#include "Hull.h"
#include "NavalBattery.h"
#include "Shell.h"

#include "drawutils.h"

#include "vec2.h"
#include "vec3.h"
#include "mat3x3.h"

#include <iostream>

bool up;
bool lup;

bool down;
bool ldown;

bool left;
bool right;

float inputTimer = 0;
float inputTimeMax = 0.5;

Transform mousePos;

//Game Controllers
Input * input = new Input();

int main()
{
	ScreenInfo SCR_INFO;
	sfw::initContext(SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT, SCR_INFO.SCR_NAME);
	Camera * mainCam = new Camera(SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT);

	float length = 136;
	int hullNum = 4;
	int mainGunNum = 4;
	Hull ** akizukiHull = new Hull*[hullNum];
	NavalBattery ** akizukiMainGuns = new NavalBattery*[mainGunNum];
	for (int i = 0; i < hullNum; ++i)
	{
		akizukiHull[i] = new Hull();
		akizukiHull[i]->radius = (length/4)/2;
		//akizukiHull[i]->transform->position = { (float)((-length/2) + (i * length / 4)), 0 };
	}
	akizukiHull[0]->transform->position = { -(17 * 3),0 };
	akizukiHull[1]->transform->position = { -(17 * 1),0 };
	akizukiHull[2]->transform->position = { (17 * 1),0 };
	akizukiHull[3]->transform->position = { (17 * 3),0 };

	for (int i = 0; i < mainGunNum; ++i)
	{
		akizukiMainGuns[i] = new NavalBattery(vec2{0,0}, 3.0f);
		akizukiMainGuns[i]->shellType1 = new Shell();
		akizukiMainGuns[i]->shellType1->setupShell("Shell", "Shell", 3, 1000, 10, 1000, 19000);
	}
	akizukiMainGuns[0]->transform->position = { -(17 * 3),0 };
	akizukiMainGuns[1]->transform->position = { -(17 * 1),0 };
	akizukiMainGuns[2]->transform->position = { (17 * 1),0 };
	akizukiMainGuns[3]->transform->position = { (17 * 3),0 };


	Ship Akizuki(akizukiHull, hullNum, akizukiMainGuns,mainGunNum);


	Akizuki.transform->dimension = { 1,1 };
	Akizuki.transform->position = { 400, 300 };
	Akizuki.horsepower = 50000;
	Akizuki.collider->mass = 3700;

	//point of ref
	Transform test;
	Akizuki.cam = mainCam;

	while (sfw::stepContext())
	{

		float t = sfw::getDeltaTime();
		mousePos.position = vec2{ sfw::getMouseX(), sfw::getMouseY() };

		inputTimer += t;
		up = sfw::getKey(KEY_UP);
		down = sfw::getKey(KEY_DOWN);
		left = sfw::getKey(KEY_LEFT);
		right = sfw::getKey(KEY_RIGHT);

		if (up && (lup != true)) {
			//printf("Up\n");
			Akizuki.enginePower += 0.1f;
			lup = true;
			ldown = false;
		}
		else if (down && (ldown != true)) {
			//printf("Down\n");
			Akizuki.enginePower -= 0.1f;
			lup = false;
			ldown = true;
		}
		else if (left) {
			Akizuki.transform->angle += 1;
		}
		else if (right) {
			Akizuki.transform->angle -= 1;
		}

		if (inputTimer >= inputTimeMax) 
		{
			lup = false;
			ldown = false;
			inputTimer = 0;
		}

		if (sfw::getMouseButton(0)) {
			test.position = Akizuki.transform->GetGlobalTransform().c[2].xy;
		}

		Akizuki.update();

		mainCam->SetupMatrix(Akizuki.transform);
		for (int i = 0; i < Akizuki.MAIN_GUNS_COUNT; ++i) {
			drawVecLine(
				(mainCam->mat * Akizuki.mainGuns[i]->transform->GetGlobalTransform()).c[2].xy,
				(mousePos.GetGlobalTransform()).c[2].xy, RED);
		}
		Akizuki.setGunAngle(mousePos.GetGlobalTransform().c[2].xy);
		Akizuki.draw();
		DrawMatrix(mainCam->mat * test.GetGlobalTransform(),30);

		//sfw::drawString(stringBitmap, playerPos.c_str(), 0, SCR_INFO.SCR_HEIGHT - 50, 15.0f, 15.0f);

	}

	sfw::termContext();
	return 0;
}