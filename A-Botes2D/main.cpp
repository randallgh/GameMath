#include "Transform.h"
#include "Collider.h"

#include "sfwdraw.h"
#include "Screen.h"
#include "Camera.h"

//Ship
#include "Ship.h"
#include "Hull.h"

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

	Camera * mainCam = new Camera();
	Akizuki.cam = mainCam;
	
	Transform test;

	/*for (int i = 0; i < 3; ++i)
	{
		akizukiHull[i]->transform->e_parent = Akizuki.transform;
	}*/

	while (sfw::stepContext())
	{
		

		vec2 target = Akizuki.transform->GetGlobalTransform().c[2].xy;
		mat3x3 proj = translate({ (float)SCR_INFO.SCR_WIDTH/2, (float)SCR_INFO.SCR_HEIGHT/2 }) * scale({ 1,1 });
		mat3x3 view = inverse(translate(target));
		mainCam->mat = proj * view;

		float t = sfw::getDeltaTime();

		inputTimer += t;

		up = sfw::getKey(KEY_UP);
		down = sfw::getKey(KEY_DOWN);
		left = sfw::getKey(KEY_LEFT);
		right = sfw::getKey(KEY_RIGHT);

		if (up && (lup != true)) {
			printf("Up\n");
			Akizuki.enginePower += 0.1f;
			lup = true;
			ldown = false;
		}
		else if (down && (ldown != true)) {
			printf("Down\n");
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

		std::cout << "X: " << sfw::getMouseX() << "Y: " << sfw::getMouseY() << std::endl;
		std::cout << "PX: " << Akizuki.transform->position.x << "PY: " << Akizuki.transform->position.y << std::endl;
		mousePos.position = vec2{ sfw::getMouseX(), sfw::getMouseY() };
		for (int i = 0; i < Akizuki.HULL_COUNT; ++i) {
			drawVecLine( 
				(mainCam->mat * Akizuki.hull[i]->transform->GetGlobalTransform()).c[2].xy ,
				(mousePos.GetGlobalTransform() * mainCam->mat).c[2].xy
				, RED, mainCam->mat.m);
		}

		
		Akizuki.draw();
		DrawMatrix(mainCam->mat * test.GetGlobalTransform(),30);

		//sfw::drawString(stringBitmap, playerPos.c_str(), 0, SCR_INFO.SCR_HEIGHT - 50, 15.0f, 15.0f);

	}

	sfw::termContext();
	return 0;
}