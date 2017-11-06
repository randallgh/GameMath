#include "sfwdraw.h"
#include "Screen.h"
#include "Camera.h"
#include "Input.h"
#include "Physics.h"

#include "Transform.h"
#include "Collider.h"
#include "Rigidbody.h"
//Ship
#include "Ship.h"
#include "Hull.h"
#include "NavalBattery.h"
#include "Shell.h"

#include "Torpedo.h"
#include "TorpedoMount.h"


#include "drawutils.h"

#include "vec2.h"
#include "vec3.h"
#include "mat3x3.h"
#include <iostream>
#include <string>

bool up;
bool lup;

bool down;
bool ldown;

bool left;
bool right;

float inputTimer = 0;
float inputTimeMax = 0.5;

unsigned int stringBitmap;
ScreenInfo SCR_INFO;

Transform mousePos(nullptr);

//Game Controllers
Camera * mainCam = new Camera();
Physics * physics = new Physics(mainCam);
Input * input = new Input();

Ship * Akizuki;
Ship * Hatsuzuki;
Ship * Suzutsuki;

//Ship* setupAkizukiClass(std::string n);
Ship* setupNewAkizukiClass(std::string n);
void pInput(float dt);
void drawGUI();

int main()
{
	sfw::initContext(SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT, SCR_INFO.SCR_NAME);
	
	mainCam->screenWidth = SCR_INFO.SCR_WIDTH; 
	mainCam->screenHeight = SCR_INFO.SCR_HEIGHT;
	stringBitmap = sfw::loadTextureMap("data/textures/fontmap.png", 16, 16);

	Akizuki = setupNewAkizukiClass("Akizuki");
	Hatsuzuki = setupNewAkizukiClass("Hatsuzuki");
	Akizuki->transform->position = vec2{ 0, 100 };

	Suzutsuki = setupNewAkizukiClass("Satsuzuki");
	Suzutsuki->transform->position = vec2{ 400,400 };
	Suzutsuki->transform->angle = 45;

	std::cout << Akizuki->name;
	

	while (sfw::stepContext())
	{
		mousePos.position = vec2{ sfw::getMouseX(), sfw::getMouseY() };
		float dt = sfw::getDeltaTime();
		pInput(dt);

		Akizuki->update(dt);
		Hatsuzuki->update(dt);
		Suzutsuki->update(dt);

		physics->update(dt);
		mainCam->SetupMatrix(Akizuki->transform);

		//Draw mouse pos as a circle
		vec2 mousePosVec = (mousePos.GetGlobalTransform()).c[2].xy;
		sfw::drawCircle(mousePosVec.x, mousePosVec.y, 5, 12, RED);
		//drawVecCircle(, 5, 12, WHITE);

		Akizuki->setWeaponsAngle(mousePos.GetGlobalTransform().c[2].xy);

		Hatsuzuki->setWeaponsAngle((mainCam->mat * Akizuki->transform->GetGlobalTransform()).c[2].xy);
		Hatsuzuki->shootAllGuns((mainCam->mat * Akizuki->transform->GetGlobalTransform()).c[2].xy);

		Suzutsuki->setWeaponsAngle((mainCam->mat * Akizuki->transform->GetGlobalTransform()).c[2].xy);

		Akizuki->draw();
		Hatsuzuki->draw();
		Suzutsuki->draw();

		//DrawMatrix(mainCam->mat * test.GetGlobalTransform(),30);
		drawGUI();

	}

	sfw::termContext();
	return 0;
}

//Ship* setupAkizukiClass(std::string n)
//{
//	Ship * ship;
//	float length = 136;
//	int hullNum = 4;
//	int mainGunNum = 4;
//	Hull ** shipHull = new Hull*[hullNum];
//	NavalBattery ** shipMainGuns = new NavalBattery*[mainGunNum];
//	for (int i = 0; i < hullNum; ++i)
//	{
//		SATGeometry col =
//		{
//			{
//				{ -15,-15 },
//				{ 15, -15 },
//				{ 15,15 },
//				{ -15,15 }
//			},
//			4
//		};
//		shipHull[i] = new Hull(col, physics);
//		shipHull[i]->name = n + " Hull";
//		shipHull[i]->tag = n + " Hull";
//		shipHull[i]->rigidbody->radius = (length / 4) / 2;
//		//akizukiHull[i]->transform->position = { (float)((-length/2) + (i * length / 4)), 0 };
//	}
//	shipHull[0]->transform->position = { -(17 * 3),0 };
//	shipHull[1]->transform->position = { -(17 * 1),0 };
//	shipHull[2]->transform->position = { (17 * 1),0 };
//	shipHull[3]->transform->position = { (17 * 3),0 };
//
//
//	for (int i = 0; i < mainGunNum; ++i)
//	{
//		shipMainGuns[i] = new NavalBattery(physics, vec2{ 0,0 }, 3.0f);
//		shipMainGuns[i]->shellType1 = new Shell();
//		shipMainGuns[i]->shellType1->setupShell(physics, "Shell", "Shell", 1, 1000, 10, 1000, 19000);
//	}
//	shipMainGuns[0]->transform->position = { -(17 * 3),0 };
//	shipMainGuns[1]->transform->position = { -(17 * 1),0 };
//	shipMainGuns[2]->transform->position = { (17 * 1),0 };
//	shipMainGuns[3]->transform->position = { (17 * 3),0 };
//
//
//	ship = new Ship(n, n, physics, shipHull, hullNum, shipMainGuns, mainGunNum);
//
//
//	ship->transform->dimension = { 1,1 };
//	ship->transform->position = { 0, 0 };
//	ship->horsepower = 50000;
//	ship->rigidbody->mass = 3700;
//
//
//	ship->cam = mainCam;
//	return ship;
//}

Ship* setupNewAkizukiClass(std::string n)
{
	Ship * ship;
	float length = 440;
	float width = 38;
	float length2 = length/2;
	float width2 = width/2;
	int hullNum = 1;
	int mainGunNum = 4;
	int torpedoMountsNum = 1;

	Hull ** shipHull = new Hull*[hullNum];
	NavalBattery ** shipMainGuns = new NavalBattery*[mainGunNum];
	TorpedoMount ** shipTorpedoMounts = new TorpedoMount*[torpedoMountsNum];

	for (int i = 0; i < hullNum; ++i)
	{
		SATGeometry col =
		{
			{
				{ -length2 + 20, width2 },
				{ -length2, width/4 },
				{ -length2, -width/4 },
				{ -length2 + 20, -width2 },
				{ length/4,-width2 },
				{ length2,-2 },
				{ length2,2 },
				{ length / 4,width2 },

			},
			8
		};
		shipHull[i] = new Hull(col, physics);
		shipHull[i]->name = n + " Hull";
		shipHull[i]->tag = n + " Hull";
		shipHull[i]->rigidbody->radius = (length / 4) / 2;
		//akizukiHull[i]->transform->position = { (float)((-length/2) + (i * length / 4)), 0 };
	}
	shipHull[0]->transform->position = { 0,0 };
	//shipHull[0]->transform->position = { -(17 * 3),0 };
	//shipHull[1]->transform->position = { -(17 * 1),0 };
	//shipHull[2]->transform->position = { (17 * 1),0 };
	//shipHull[3]->transform->position = { (17 * 3),0 };


	for (int i = 0; i < mainGunNum; ++i)
	{
		shipMainGuns[i] = new NavalBattery(physics, vec2{ 0,0 }, 3.0f);
		shipMainGuns[i]->shellType1 = new Shell();
		shipMainGuns[i]->shellType1->setupShell(physics, "Shell", "Shell", 1, 1000, 10, 1000, 19000);
	}
	shipMainGuns[0]->transform->position = { 100 + 30,0 };
	shipMainGuns[1]->transform->position = { 100 ,0 };
	shipMainGuns[2]->transform->position = { -100,0 };
	shipMainGuns[3]->transform->position = { -100 - 30,0 };

	for (int i = 0; i < torpedoMountsNum; ++i)
	{
		shipTorpedoMounts[i] = new TorpedoMount(physics, vec2{ 0,0 });
	}
	shipTorpedoMounts[0]->transform->position = { -50,0 };

	ship = new Ship(n, n, physics, 
		shipHull, hullNum, 
		shipMainGuns, mainGunNum,
		shipTorpedoMounts,torpedoMountsNum);

	ship->transform->dimension = { 1,1 };
	ship->transform->position = { 0, 0 };
	ship->horsepower = 50000;
	ship->rigidbody->mass = 3700;


	ship->cam = mainCam;
	return ship;
}


void pInput(float dt)
{
	inputTimer += dt;
	up = sfw::getKey(KEY_UP) || sfw::getKey(KEY_W);
	down = sfw::getKey(KEY_DOWN) || sfw::getKey(KEY_S);
	left = sfw::getKey(KEY_LEFT) || sfw::getKey(KEY_A);
	right = sfw::getKey(KEY_RIGHT) || sfw::getKey(KEY_D);

	if (up && (lup != true)) {
		//printf("Up\n");
		Akizuki->enginePower += 0.1f;
		lup = true;
		ldown = false;
	}
	else if (down && (ldown != true)) {
		//printf("Down\n");
		Akizuki->enginePower -= 0.1f;
		lup = false;
		ldown = true;
	}
	else if (left) {
		Akizuki->transform->angle += 1;
	}
	else if (right) {
		Akizuki->transform->angle -= 1;
	}

	if (inputTimer >= inputTimeMax)
	{
		lup = false;
		ldown = false;
		inputTimer = 0;
	}

	if (sfw::getMouseButton(0))
	{
		Akizuki->shootAllGuns((mousePos.GetGlobalTransform()).c[2].xy);
	}
}

void drawGUI()
{
	//Draw Ui
	for (int i = 0; i < Akizuki->MAIN_GUNS_COUNT; ++i)
	{
		std::string re = " NULL ";
		if (Akizuki->mainGuns[i]->reloadTimer >= Akizuki->mainGuns[i]->reloadTime)
		{
			re = "Reloaded";
		}
		else
		{
			re = std::to_string(Akizuki->mainGuns[i]->reloadTimer) + " / " + std::to_string(Akizuki->mainGuns[i]->reloadTime);
		}
		sfw::drawString(stringBitmap, re.c_str(), 0, SCR_INFO.SCR_HEIGHT - (20 * i), 15.0f, 15.0f);
	}

	std::string engine = "Engine Power: " + std::to_string(Akizuki->enginePower * 100);
	sfw::drawString(stringBitmap, engine.c_str(), 0, SCR_INFO.SCR_HEIGHT - 80, 15.0f, 15.0f);

	//Debug info
	vec2 pos = (Akizuki->transform->GetGlobalTransform()).c[2].xy;

	vec2 posCam = (mainCam->mat * Akizuki->transform->GetGlobalTransform()).c[2].xy;
	sfw::drawString(stringBitmap, "Player", posCam.x - 50, posCam.y + 50, 15.0f, 15.0f);

	std::string posS = "Akizuki X: " + std::to_string(pos.x) + " Y: " + std::to_string(pos.y);
	sfw::drawString(stringBitmap, posS.c_str(), 0, SCR_INFO.SCR_HEIGHT - 100, 15.0f, 15.0f);

	pos = (Hatsuzuki->transform->GetGlobalTransform()).c[2].xy;
	posS = "Hatsuzuki X: " + std::to_string(pos.x) + " Y: " + std::to_string(pos.y);
	sfw::drawString(stringBitmap, posS.c_str(), 0, SCR_INFO.SCR_HEIGHT - 120, 15.0f, 15.0f);

	sfw::drawString(stringBitmap, std::to_string(1 / sfw::getDeltaTime()).c_str(), SCR_INFO.SCR_WIDTH - 100, SCR_INFO.SCR_HEIGHT, 25.0f, 25.0f);
}