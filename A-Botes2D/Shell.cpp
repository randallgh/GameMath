#include "Shell.h"
#include "Transform.h"
#include "Collider.h"
#include "sfwdraw.h"
#include "drawutils.h"
#include "Ship.h"
#include "Camera.h"

#include <string>

Shell::Shell()
{
	tag = "THIS IS A BIG ASS SHITTING TAG";
	name = "THIS IS A BIG ASS SHITTING NAME";
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

void Shell::setupShell(std::string t, std::string n, float r, float spe, 
					   float lif, float dam, int mDis)
{
	tag = t;
	name = n;
	radius = r;
	speed = spe;

	maxLife = lif;
	life = 0;

	damage = dam;
	maxDistance = mDis;

	transform = new Transform();
	collider = new Collider(this);

	isEnabled = false;
}

void Shell::setupShell(const Shell &s)
{
	tag = s.tag;
	name = s.name;
	radius = s.radius;
	speed = s.speed;

	maxLife = s.maxLife;
	life = 0;

	damage = s.damage;
	maxDistance = s.maxDistance;

	transform = new Transform();
	collider = new Collider(this);

	isEnabled = false;
}

void Shell::setupShell(const Shell * s)
{
	//tag.resize((*s).tag.length());
	tag = (*s).tag;
	name = (*s).name;
	radius = (*s).radius;
	speed = (*s).speed;

	maxLife = (*s).maxLife;
	life = 0;

	damage = (*s).damage;
	maxDistance = (*s).maxDistance;

	transform = new Transform();
	collider = new Collider(this);

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
	collider->update();
}

void Shell::draw()
{
	if (!isEnabled) { return; }
	drawVecCircle((parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy, radius, 12);
	//DrawMatrix(parentShip->cam->mat * transform->GetGlobalTransform(), 10);
}
