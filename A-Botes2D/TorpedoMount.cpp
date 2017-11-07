#include "TorpedoMount.h"

#include "sfwdraw.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "drawutils.h"


#include "Torpedo.h"
#include "Ship.h"
#include "Camera.h"

#include <iostream>

TorpedoMount::TorpedoMount(Physics * phys, const vec2 & pos)
{
	physics = phys;
	isEnabled = true;
	transform = new Transform(this);
	rigidbody = new Rigidbody(this);

	transform->position = pos;

	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		torpedos[i] = nullptr;
	}
}


TorpedoMount::~TorpedoMount()
{
	//delete transform;
	//delete rigidbody;
}

void TorpedoMount::update(float dt)
{
	if (!isEnabled) { return; }
	reloadTimer += dt;
	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		if (torpedos[i] == nullptr || !torpedos[i]->isEnabled) { continue; }
		torpedos[i]->update(dt);
	}
}

void TorpedoMount::draw(mat3x3 cam)
{
	if (!isEnabled) { return; }
	DrawMatrix(cam * transform->GetGlobalTransform(), 20);
	drawVecCircle((cam * transform->GetGlobalTransform()).c[2].xy, 10, 12, RED);
	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		if (torpedos[i] == nullptr || !torpedos[i]->isEnabled) { continue; }
		torpedos[i]->draw(cam);
	}
}

void TorpedoMount::launchAll(vec2 pos)
{
	if (reloadTimer >= reloadTime)
	{
		Torpedo * torp = findNextTorp();
		if (torp != nullptr)
		{
			torp->setup(physics, torpedo);
			torp->parentMount = this;
			torp->reset();
			torp->transform->position = transform->GetGlobalTransform().c[2].xy;

			vec2 norm = normal(pos - (parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy);
			torp->transform->position += norm * 50;
			torp->rigidbody->velocity = norm * torpedo->speed;
			torp->transform->angle = VectorToDegree(norm);
			reloadTimer = 0;
		}
	}
}

Torpedo * TorpedoMount::findNextTorp()
{
	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		if (torpedos[i] == nullptr)
		{
			torpedos[i] = new Torpedo();
			torpedos[i]->isEnabled = false;
			++numTorpedoes;
			return torpedos[i];
		}
		if (!torpedos[i]->isEnabled)
		{
			return torpedos[i];
		}
	}
	return nullptr;
}
