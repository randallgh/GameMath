#include "Torpedo.h"

#include "Collider.h"
#include "Transform.h"
#include "Rigidbody.h"

#include "sfwdraw.h"

Torpedo::Torpedo()
{
	tag = "Torpedo";
	name = "Torpedo";
	speed = 0;
	life = 0;
	maxLife = 0;
	isEnabled = false;
	color = WHITE;
}

Torpedo::~Torpedo()
{
	//Delete dymically allocated memory here
}

void Torpedo::setup(Physics * phys, std::string n, float w, float length, float s, float l, float dam, float mDis)
{
	tag = "Torpedo";
	name = n;

	speed = s * 1.68781;

	maxLife = l;
	life = 0;

	damage = dam;
	maxDistance = mDis;

	isEnabled = true;

	this->length = length;
	width = w;

	float l2 = this->length / 2;
	float w2 = width / 2;
	SATGeometry geo =
	{
		{
			{ -l2,-w2 },
			{ l2,-w2 },
			{ l2,w2 },
			{ -l2,w2 }
		},
		4
	};

	if (transform == nullptr) { transform = new Transform(this); }
	if (collider == nullptr) { collider = new Collider(geo, this, phys); }
	if (rigidbody == nullptr) { rigidbody = new Rigidbody(this); }

	collider->geometry = geo;
	isEnabled = false;
	color = WHITE;
}

void Torpedo::setup(Physics * phys, const Torpedo * torp)
{
	tag = "Torpedo";
	name = torp->name;

	speed = torp->speed;

	maxLife = torp->maxLife;
	life = 0;

	damage = torp->damage;
	maxDistance = torp->maxDistance;

	isEnabled = true;

	length = torp->length;
	width = torp->width;

	float l2 = length / 2;
	float w2 = width / 2;

	SATGeometry geo =
	{
		{
			{ -l2,-w2 },
			{ l2,-w2 },
			{ l2,w2 },
			{ -l2,w2 }
		},
		4
	};

	if (transform == nullptr) { transform = new Transform(this); }
	if (collider == nullptr) { collider = new Collider(geo,this,phys); }
	if (rigidbody == nullptr) { rigidbody = new Rigidbody(this); }

	collider->geometry = geo;
	isEnabled = false;
}

void Torpedo::reset()
{
	life = 0;
	distanceTraveled = 0;
	isEnabled = true;
}

void Torpedo::update(float dt)
{
	if (!isEnabled) { return; }
	life += dt;
	distanceTraveled += magnitude(rigidbody->velocity) * dt;
	if (distanceTraveled >= maxDistance) { isEnabled = false; return; }
}

void Torpedo::draw(mat3x3 cam)
{
	if (!isEnabled) { return; }
	collider->draw(cam * transform->GetGlobalTransform());
}
