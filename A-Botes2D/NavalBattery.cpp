#include "NavalBattery.h"

#include "sfwdraw.h"

//Game
#include "Ship.h"
#include "Shell.h"

//SfwGame
#include "Transform.h"
#include "Camera.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Physics.h"

#include <iostream>

NavalBattery::NavalBattery(Physics * phys, vec2 pos, float reload)
{
	isEnabled = true;
	transform = new Transform(this);
	//rigidbody = new Rigidbody(this);
	physics = phys;

	reloadTime = reload;
	reloadTimer = 0;

	MAX_SHELLS = 20;

	for (int i = 0; i < MAX_SHELLS; ++i) 
	{
		shells[i] = nullptr;
	}
}

NavalBattery::~NavalBattery()
{
}

void NavalBattery::update(float dt)
{
	if (!isEnabled) { return; }
	reloadTimer += dt;
	for (int i = 0; i < MAX_SHELLS; ++i)
	{
		if (shells[i] == nullptr || !shells[i]->isEnabled) { continue; }
		shells[i]->update(dt);
	}
}

void NavalBattery::draw()
{
	if (!isEnabled) { return; }
	DrawMatrix(parentShip->cam->mat * transform->GetGlobalTransform(), 20);
	for (int i = 0; i < MAX_SHELLS; ++i) 
	{
		if (shells[i] == nullptr || !shells[i]->isEnabled) { continue; }
		shells[i]->draw();
	}
}

void NavalBattery::shoot(vec2 pos)
{
	if (reloadTimer >= reloadTime) 
	{
		for (int i = 0; i < numBarrels; ++i)
		{
			Shell * shell = findNextShell();
			if (shell != nullptr)
			{
				vec2 norm = normal(pos - (parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy);
				//std::cout << "Pos X: " << pos.x << "Y: " << pos.y << std::endl;
				shell->setupShell(shellType1, physics);
				shell->parentShip = parentShip;
				shell->reset();


				shell->transform->position = vec2{ 0,0 };
				shell->transform->e_parent = this->transform;
				if (numBarrels > 1)
				{
					float distanceBetweenGuns = 4;
					shell->transform->position -= vec2{ 0,(-distanceBetweenGuns / 2 * (float)numBarrels - 1) } +i * vec2{ 0 ,distanceBetweenGuns };
				}
				shell->transform->position = shell->transform->GetGlobalTransform().c[2].xy;
				shell->transform->e_parent = nullptr;
				shell->transform->angle = VectorToDegree(norm);
				//std::cout << "Norm X: " << norm.x << "Y: " << norm.y << std::endl;

				float dist = distance(pos, (parentShip->cam->mat * transform->GetGlobalTransform()).c[2].xy);
				shell->maxDistance = dist;
				//std::cout << dist << std::endl;

				shell->rigidbody->velocity = norm * shell->speed; //degreeToVector(transform->angle + parentShip->transform->angle,1) * shell->speed;
				reloadTimer = 0;
			}
		}
	}
}

Shell * NavalBattery::findNextShell()
{
	for (int i = 0; i < MAX_SHELLS; ++i) 
	{
		if (shells[i] == nullptr)
		{
			shells[i] = new Shell();
			shells[i]->isEnabled = false;
			++numShells;
			return shells[i];
		}
		if (!shells[i]->isEnabled) 
		{
			return shells[i];
		}
	}
	return nullptr;
}
