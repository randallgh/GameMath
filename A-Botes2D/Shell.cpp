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
	color = WHITE;
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

	SATGeometry shell =
	{
		{
			{ -r,-r },
			{ 0,r },
			{ -r,r }
		},
		3
	};
	color = WHITE;
	isEnabled = true;
	if (transform == nullptr){ transform = new Transform(this); }
	if (collider == nullptr) { collider = new Collider(shell, this, phys); }
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

	SATGeometry shell =
	{
		{
			{ -s.rigidbody->radius,-s.rigidbody->radius },
			{ 0,s.rigidbody->radius },
			{ -s.rigidbody->radius,s.rigidbody->radius }
		},
		3
	};
	color = WHITE;
	isEnabled = true;
	if (transform == nullptr) { transform = new Transform(this); }
	if (collider == nullptr){ collider = new Collider(shell, this, phys); }
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

	SATGeometry shell =
	{
		{
			{ -(*s).rigidbody->radius,-(*s).rigidbody->radius },
			{ 0,(*s).rigidbody->radius },
			{ -(*s).rigidbody->radius,(*s).rigidbody->radius }
		},
		3
	};
	color = WHITE;
	isEnabled = true;
	if (transform == nullptr) { transform = new Transform(this); }
	if (collider == nullptr) { collider = new Collider(shell, this, phys); }
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

void Shell::update(float dt)
{
	if (!isEnabled) { return; }
	//life += dt;
	distanceTraveled += magnitude(rigidbody->velocity) * dt;
	if (distanceTraveled >= maxDistance) { isEnabled = false; return; }
	//rigidbody->update();
	//std::cout << distanceTraveled << std::endl;
	//std::cout << magnitude(collider->velocity) << std::endl;
}

void Shell::draw(mat3x3 cam)
{
	if (!isEnabled) { return; }
	collider->draw(cam * transform->GetGlobalTransform());
	//drawVecCircle((parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy, rigidbody->radius, 4);
	//DrawMatrix(parentShip->cam->mat * transform->GetGlobalTransform(), 10);
}
