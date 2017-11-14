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
		for (int i = 0; i < numTorpTubes; ++i)
		{
			Torpedo * torp = findNextTorp();
			if (torp != nullptr)
			{
				vec2 norm = normal(pos - (parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy);

				torp->setup(physics, torpedo);
				torp->parentMount = this;
				torp->reset();

				torp->transform->position = vec2{ 0,0 };
				torp->transform->e_parent = this->transform;
				
				if (numTorpTubes > 1)
				{
					float distanceBetweenMounts = 8;
					torp->transform->position -= vec2{ 0,(-distanceBetweenMounts / 2 * (float)numTorpTubes - 1) } +i * vec2{ 0 ,distanceBetweenMounts };
				}
				
				torp->transform->position = torp->transform->GetGlobalTransform().c[2].xy;
				torp->transform->e_parent = nullptr;

				torp->transform->angle = VectorToDegree(norm);

				torp->transform->position += norm * 50;
				torp->rigidbody->velocity = norm * torpedo->speed;
				reloadTimer = 0;
			}
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
