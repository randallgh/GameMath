#include "Shell.h"
#include "Transform.h"
#include "Collider.h"
#include "sfwdraw.h"

Shell::Shell()
{
	tag = "null";
	name = "null";
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
	if (life >= maxLife || distanceTraveled >= maxDistance) { isEnabled == false; return; }
	collider->update();
}

void Shell::draw()
{
}
