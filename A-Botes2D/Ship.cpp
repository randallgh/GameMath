#include "Ship.h"
#include "Hull.h"
#include "vec2.h"
#include "Transform.h"
#include "Collider.h"
#include "mathutils.h"
#include "sfwdraw.h"
#include "Camera.h"
#include "NavalBattery.h"

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
		DrawMatrix(cam->mat * hull[i]->transform->GetGlobalTransform(), hull[i]->radius);
	}

	//DrawMatrix(transform->GetGlobalTransform(), 30);
}
