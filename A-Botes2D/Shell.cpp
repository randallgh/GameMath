#include "Shell.h"
#include "Transform.h"
#include "Collider.h"
#include "sfwdraw.h"
#include "drawutils.h"
#include "Ship.h"
#include "Camera.h"
#include "vec2.h"
#include "Physics.h"
#include "Rigidbody.h"

#include <string>
#include <iostream>

Shell::Shell()
{
	tag = "Shell";
	name = "Shell";
	speed = 0;
	life = 0;
	maxLife = 0;
	damage = 0;
	isEnabled = false;
}


Shell::~Shell()
{
	//delete transform;
	//delete collider;
}

void Shell::setupShell(Physics * phys, std::string t, std::string n, float r, float spe, 
					   float lif, float dam, int mDis)
{
	tag = t;
	name = n;
	
	speed = spe;

	maxLife = lif;
	life = 0;

	damage = dam;
	maxDistance = mDis;

	isEnabled = true;
	transform = new Transform();
	if (collider == nullptr) { collider = new Collider(this, phys); }
	if (rigidbody == nullptr) { rigidbody = new Rigidbody(this); }
	rigidbody->radius = r;
	isEnabled = false;
}

void Shell::setupShell(const Shell &s, Physics * phys)
{
	tag = s.tag;
	name = s.name;
	speed = s.speed;

	maxLife = s.maxLife;
	life = 0;

	damage = s.damage;
	maxDistance = s.maxDistance;

	isEnabled = true;
	transform = new Transform();
	if (collider == nullptr){ collider = new Collider(this, phys); }
	if (rigidbody == nullptr) { rigidbody = new Rigidbody(this); }
	rigidbody->radius = s.rigidbody->radius;
	isEnabled = false;
}

void Shell::setupShell(const Shell * s, Physics * phys)
{
	//tag.resize((*s).tag.length());
	tag = (*s).tag;
	name = (*s).name;
	
	speed = (*s).speed;

	maxLife = (*s).maxLife;
	life = 0;

	damage = (*s).damage;
	maxDistance = (*s).maxDistance;

	isEnabled = true;
	transform = new Transform();
	if (collider == nullptr) { collider = new Collider(this, phys); }
	if (rigidbody == nullptr) { rigidbody = new Rigidbody(this); }
	rigidbody->radius = (*s).rigidbody->radius;
	isEnabled = false;
}

void Shell::reset()
{
	life = 0;
	distanceTraveled = 0;
	isEnabled = true;
}

void Shell::update()
{
	if (!isEnabled) { return; }
	life += sfw::getDeltaTime();
	if (life >= maxLife || distanceTraveled >= maxDistance) { isEnabled = false; return; }
	//rigidbody->update();
	//std::cout << distanceTraveled << std::endl;
	//std::cout << magnitude(collider->velocity) << std::endl;
	distanceTraveled += magnitude(rigidbody->velocity) * sfw::getDeltaTime();
}

void Shell::draw()
{
	if (!isEnabled) { return; }
	drawVecCircle((parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy, rigidbody->radius, 12);
	//DrawMatrix(parentShip->cam->mat * transform->GetGlobalTransform(), 10);
}
