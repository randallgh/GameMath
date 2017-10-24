#include "Physics.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"

#include <iostream>

#include "sfwdraw.h"

Physics::Physics()
{
	colliders = new Collider*[MAX_COLLIDERS];
	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		colliders[i] = nullptr;
	}
}

Physics::~Physics()
{

}

void Physics::update()
{
	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		//if (!colliders[i].isEnabled) { continue; };
		colliders[i]->update();
	}

	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		//|| !colliders[i].gameObject->enabled
		if (colliders[i] == nullptr) { continue; };
		if (!colliders[i]->gameObject->isEnabled) { continue; };

		for (int o = 1; o < MAX_COLLIDERS; ++o)
		{
			if (colliders[i] == nullptr) { continue; };
			if (!colliders[o]->gameObject->isEnabled) { continue; };
			if (i != o)
			{
				//std::cout << "Checking COLLISION" << std::endl;
				float dist = 
					distance(colliders[i]->gameObject->transform->GetGlobalTransform().c[2].xy,
					colliders[o]->gameObject->transform->GetGlobalTransform().c[2].xy);
				if (dist <= (colliders[i]->radius + colliders[o]->radius))
				{
					//colliders[i]->collided = colliders[o];
					//colliders[o]->collided = colliders[i];

					std::cout << "[WARNING - PHYSICS] Unhandled Collision: "
						<< std::endl
						<< i
						<< " "
						<< colliders[i]->gameObject->name
						<< " X: " << colliders[i]->gameObject->transform->position.x
						<< " Y: " << colliders[i]->gameObject->transform->position.y
						<< " AND "
						<< std::endl
						<< o
						<< " "
						<< colliders[o]->gameObject->name
						<< " X: " << colliders[o]->gameObject->transform->position.x
						<< " Y: " << colliders[o]->gameObject->transform->position.y
						<< std::endl
						<< "Distance: "
						<< dist
						<< std::endl;

				}
			}
		}
	}
}


bool Physics::addCollider(Collider * collider)
{
	//std::cout << "Trying to add collider" << std::endl;
	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr) {
			std::cout << "[INFO - PHYSICS] ADDED COLLIDER AT: " << i << " X: " << collider->gameObject->transform->position.x << " Y: " << collider->gameObject->transform->position.y << std::endl;
			colliders[i] = collider;
			return true;
		}
		else if (!colliders[i]->gameObject->isEnabled && !(colliders[i]->gameObject->tag.compare("Bullet") == 0) && !(colliders[i]->gameObject->tag.compare("EBullet") == 0))
		{
			std::cout << "[INFO - PHYSICS] EDITED COLLIDER AT: " << i << " X: " << collider->gameObject->transform->position.x << " Y: " << collider->gameObject->transform->position.y << std::endl;
			colliders[i] = collider;
			return true;
		}
	}
	return false;
}

int Physics::isCollide(int i, int o, std::string tag1, std::string tag2)
{
	if (colliders[i]->gameObject->tag.compare(tag1) == 0 && colliders[o]->gameObject->tag.compare(tag2) == 0)
	{
		//std::cout << colliders[i]->gameObject->gameObject->tag << " " << colliders[o]->gameObject->gameObject->tag << " COLLISION" << std::endl;
		return 0;
	}
	else if (colliders[i]->gameObject->tag.compare(tag2) == 0 && colliders[o]->gameObject->tag.compare(tag1) == 0)
	{
		//std::cout << colliders[i]->gameObject->gameObject->tag << " " << colliders[o]->gameObject->gameObject->tag << " COLLISION" << std::endl;
		return 1;
	}
	return -1;
}
