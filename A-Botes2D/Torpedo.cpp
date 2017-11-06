#include "Torpedo.h"

#include "Collider.h"
#include "Transform.h"

Torpedo::Torpedo()
{
	tag = "Torpedo";
	name = "Torpedo";
	speed = 0;
	life = 0;
	maxLife = 0;
	isEnabled = false;
}

Torpedo::~Torpedo()
{
	//Delete dymically allocated memory here
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

}

void Torpedo::draw(mat3x3 cam)
{
	if (!isEnabled) { return; }
	collider->draw(cam * transform->GetGlobalTransform());
}
