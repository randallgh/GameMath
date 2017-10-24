#include "Ship.h"
#include "Hull.h"
#include "vec2.h"
#include "Transform.h"
#include "Collider.h"
#include "mathutils.h"
#include "sfwdraw.h"
#include "Camera.h"
#include "NavalBattery.h"
#include <iostream>

Ship::Ship()
{

}

Ship::Ship( Hull ** h, int hc, NavalBattery ** mG, int mGC)
{
	hull = h;
	mainGuns = mG;
	HULL_COUNT = hc;
	MAIN_GUNS_COUNT = mGC;

	transform = new Transform();
	collider = new Collider(this);
	isEnabled = true;

	for (int i = 0; i < HULL_COUNT; ++i)
	{
		hull[i]->transform->e_parent = transform;
	}

	for (int i = 0; i < MAIN_GUNS_COUNT; ++i)
	{
		mainGuns[i]->transform->e_parent = transform;
	}
}

Ship::~Ship()
{

}

void Ship::setGunAngle(vec2 pos)
{
	for (int i = 0; i < MAIN_GUNS_COUNT; ++i) 
	{
		vec2 normalVec = normal(pos - (cam->mat * mainGuns[i]->transform->GetGlobalTransform()).c[2].xy);
		mainGuns[i]->transform->angle = VectorToDegree(normalVec) - transform->angle;
		std::cout << mainGuns[i]->transform->angle - transform->angle << std::endl;
	}
}

void Ship::update()
{
	clamp(enginePower,1,0);
	collider->velocity = degreeToVector( transform->angle, 1) * ((horsepower / collider->mass) * enginePower) * 10;
	collider->update();

	for (int i = 0; i < HULL_COUNT; ++i)
	{
		hull[i]->update();
	}

}

void Ship::draw()
{
	for (int i = 0; i < HULL_COUNT; ++i) 
	{
		vec2 pos = (cam->mat * hull[i]->transform->GetGlobalTransform()).c[2].xy;
		//DrawMatrix(cam->mat * hull[i]->transform->GetGlobalTransform(), 20);
		sfw::drawCircle(pos.x, pos.y, hull[i]->radius, 12, WHITE);
	}
	for (int i = 0; i < HULL_COUNT; ++i)
	{
		vec2 pos = (cam->mat * hull[i]->transform->GetGlobalTransform()).c[2].xy;
		DrawMatrix(cam->mat * mainGuns[i]->transform->GetGlobalTransform(), 20);
		sfw::drawCircle(pos.x, pos.y, 10, 12, YELLOW);
	}
	//DrawMatrix(transform->GetGlobalTransform(), 30);
}
