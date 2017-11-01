#include "Ship.h"
#include "Hull.h"
#include "vec2.h"
#include "Transform.h"
#include "Collider.h"
#include "mathutils.h"
#include "sfwdraw.h"
#include "Camera.h"
#include "NavalBattery.h"
#include "Physics.h"
#include "Rigidbody.h"
#include <iostream>

Ship::Ship()
{

}

Ship::Ship(std::string t, std::string n, Physics * phys, Hull ** h, int hc, NavalBattery ** mG, int mGC)
{
	tag = t;
	name = n;

	hull = h;
	mainGuns = mG;
	HULL_COUNT = hc;
	MAIN_GUNS_COUNT = mGC;

	transform = new Transform(this);
	//collider = new Collider(this, phys);
	rigidbody = new Rigidbody(this);
	isEnabled = true;

	for (int i = 0; i < HULL_COUNT; ++i)
	{
		hull[i]->transform->e_parent = transform;
	}

	for (int i = 0; i < MAIN_GUNS_COUNT; ++i)
	{
		mainGuns[i]->transform->e_parent = transform;
		mainGuns[i]->parentShip = this;
	}
}

Ship::~Ship()
{

}



void Ship::setup(std::string t, std::string n, Physics * phys, Hull ** h, int hc, NavalBattery ** mG, int mGC)
{
	tag = t;
	name = n;

	hull = h;
	mainGuns = mG;
	HULL_COUNT = hc;
	MAIN_GUNS_COUNT = mGC;

	transform = new Transform(this);
	rigidbody = new Rigidbody(this);
	//collider = new Collider(this, phys);
	isEnabled = true;

	for (int i = 0; i < HULL_COUNT; ++i)
	{
		hull[i]->transform->e_parent = transform;
	}

	for (int i = 0; i < MAIN_GUNS_COUNT; ++i)
	{
		mainGuns[i]->transform->e_parent = transform;
		mainGuns[i]->parentShip = this;
	}
}

void Ship::shootAllGuns(vec2 pos)
{
	for (int i = 0; i < MAIN_GUNS_COUNT; ++i) 
	{
		mainGuns[i]->shoot(pos);
	}
}

void Ship::setGunAngle(vec2 pos)
{
	for (int i = 0; i < MAIN_GUNS_COUNT; ++i) 
	{
		vec2 normalVec = normal(pos - (cam->mat * mainGuns[i]->transform->GetGlobalTransform()).c[2].xy);
		mainGuns[i]->transform->angle = VectorToDegree(normalVec) - transform->angle;
		//std::cout << mainGuns[i]->transform->angle - transform->angle << std::endl;
	}
}

void Ship::update(float dt)
{
	clamp(enginePower,1,0);
	rigidbody->velocity = degreeToVector( transform->angle, 1) * ((horsepower / rigidbody->mass) * enginePower) * 10;
	rigidbody->update(dt);

	for (int i = 0; i < HULL_COUNT; ++i)
	{
		hull[i]->update();
	}
	for (int i = 0; i < MAIN_GUNS_COUNT; ++i) 
	{
		mainGuns[i]->update();
	}

}

void Ship::draw()
{
	DrawMatrix(cam->mat * transform->GetGlobalTransform(), 20);

	for (int i = 0; i < HULL_COUNT; ++i) 
	{
		if (!hull[i]->isEnabled) { continue; }
		//vec2 pos = (cam->mat * hull[i]->transform->GetGlobalTransform()).c[2].xy;
		//DrawMatrix(cam->mat * hull[i]->transform->GetGlobalTransform(), 20);
		//sfw::drawCircle(pos.x, pos.y, hull[i]->rigidbody->radius, 12, WHITE);
		hull[i]->draw(cam->mat);
	}
	for (int i = 0; i < MAIN_GUNS_COUNT; ++i)
	{
		vec2 pos = (cam->mat * mainGuns[i]->transform->GetGlobalTransform()).c[2].xy;
		//DrawMatrix(cam->mat * mainGuns[i]->transform->GetGlobalTransform(), 20);
		//sfw::drawCircle(pos.x, pos.y, 10, 12, YELLOW);
		mainGuns[i]->draw();
	}
	//DrawMatrix(transform->GetGlobalTransform(), 30);
}
