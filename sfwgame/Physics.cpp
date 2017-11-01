#include "Physics.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Rigidbody.h"

#include <iostream>

#include "sfwdraw.h"

Physics::Physics(Camera * c)
{
	cam = c;
	colliders = new Collider*[MAX_COLLIDERS];
	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		colliders[i] = nullptr;
	}
}

Physics::~Physics()
{

}

void Physics::update(float dt)
{
	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr) { continue; }
		if (colliders[i]->gameObject == nullptr) { continue; }
		if (colliders[i]->gameObject->rigidbody == nullptr) { continue; }
		colliders[i]->gameObject->rigidbody->update(dt);
	}

	for (int i = 0; i < MAX_COLLIDERS; ++i)
	{
		//|| !colliders[i].gameObject->enabled
		if (colliders[i] == nullptr) { continue; };
		if (!colliders[i]->gameObject->isEnabled) { continue; };
		//if (colliders[i]->type == ColliderType::SAT) { continue; }

		for (int o = 1; o < MAX_COLLIDERS; ++o)
		{
			if (colliders[o] == nullptr) { continue; };
			if (!colliders[o]->gameObject->isEnabled) { continue; };
			//if (colliders[i]->type == ColliderType::SAT) { continue; }

			if (i != o)
			{
				float dist =
					distance(
					(cam->mat *
						colliders[i]->gameObject->transform->GetGlobalTransform()).c[2].xy,
						(cam->mat *
							colliders[o]->gameObject->transform->GetGlobalTransform()).c[2].xy)
					;
				
				//std::cout << "Checking COLLISION" << std::endl;
				Collision collision = colliders[i]->doesCollide(colliders[o]);

				if (collision.penetration > 0)
				{					
					if (colliders[i]->gameObject->tag.compare("Akizuki Hull") == 0 && colliders[o]->gameObject->tag.compare("Hatsuzuki Hull") == 0)
					{
						colliders[i]->gameObject->transform->e_parent->gameObject->transform->position 
							+= (collision.collisionNormal * collision.penetration)/2;
						colliders[o]->gameObject->transform->e_parent->gameObject->transform->position 
							-= (collision.collisionNormal * collision.penetration)/2;
					}

					vec2 posI = (cam->mat *
						colliders[i]->gameObject->transform->GetGlobalTransform()).c[2].xy;
					vec2 posO = (cam->mat *
						colliders[o]->gameObject->transform->GetGlobalTransform()).c[2].xy;

					std::cout << "[WARNING - PHYSICS] Unhandled Collision SAT_SAT: "
						<< std::endl
						<< i
						<< " "
						<< colliders[i]->gameObject->name
						<< " X: " << posI.x
						<< " Y: " << posI.y
						<< " AND "
						<< std::endl
						<< o
						<< " "
						<< colliders[o]->gameObject->name
						<< " X: " << posO.x
						<< " Y: " << posO.y
						<< std::endl
						<< "Distance: "
						<< dist
						<< std::endl;
					continue;
				}

				if (dist <= (colliders[i]->gameObject->rigidbody->radius 
					+ colliders[o]->gameObject->rigidbody->radius))
				{
					//colliders[i]->collided = colliders[o];
					//colliders[o]->collided = colliders[i];

					//colliders[o]->gameObject->tag.resize(colliders[o]->gameObject->tag.size());
					//colliders[i]->gameObject->tag.resize(colliders[i]->gameObject->tag.size());

					switch (isCollide(i, o, "Shell"))
					{
					case 0:
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Akizuki Hull"))
					{
					case 0:
						continue;
					default:
						break;
					}
					switch (isCollide(i, o, "Hatsuzuki Hull"))
					{
					case 0:
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Akizuki","Akizuki Hull"))
					{
					case 0:
						continue;
					case 1:
						continue;
					default:
						break;
					}
					switch (isCollide(i, o, "Hatsuzuki", "Hatsuzuki Hull"))
					{
					case 0:
						continue;
					case 1:
						continue;
					default:
						break;
					}
					switch (isCollide(i, o, "Akizuki", "Hatsuzuki"))
					{
					case 0:
						continue;
					case 1:
						continue;
					default:
						break;
					}
					switch (isCollide(i, o, "Akizuki Hull", "Hatsuzuki Hull"))
					{
					case 0:
						continue;
					case 1:
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Akizuki", "Hatsuzuki Hull"))
					{
					case 0:
						continue;
					case 1:
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Akizuki Hull", "Hatsuzuki"))
					{
					case 0:
						continue;
					case 1:
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Shell", "Hatsuzuki Hull"))
					{
					case 0:
						//tag1 == tag2 = 0
						//Shell Hatsuzuki
						//i		o
						colliders[i]->gameObject->isEnabled = false;
						continue;
					case 1:
						//tag2 == tag1 = 1
						//Hatsuzuki  Shell
						//i		  o
						//std::cout << "Damaged Hatsuzuki" << std::endl;
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Shell", "Akizuki Hull"))
					{
					case 0:
						//tag1 == tag2 = 0
						//Shell Hatsuzuki
						//i		o
						//colliders[i]->gameObject->isEnabled = false;
						continue;
					case 1:
						//tag2 == tag1 = 1
						//Hatsuzuki  Shell
						//i		  o
						//std::cout << "Damaged Akizuki" << std::endl;
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Shell", "Hatsuzuki"))
					{
					case 0:
						//tag1 == tag2 = 0
						//Shell Hatsuzuki
						//i		o
						colliders[i]->gameObject->isEnabled = false;
						continue;
					case 1:
						//tag2 == tag1 = 1
						//Hatsuzuki  Shell
						//i		  o
						//std::cout << "Damaged Hatsuzuki" << std::endl;
						continue;
					default:
						break;
					}

					switch (isCollide(i, o, "Shell", "Akizuki"))
					{
					case 0:
						//tag1 == tag2 = 0
						//Shell Hatsuzuki
						//i		o
						//colliders[i]->gameObject->isEnabled = false;
						continue;
					case 1:
						//tag2 == tag1 = 1
						//Hatsuzuki  Shell
						//i		  o
						//std::cout << "Damaged Akizuki" << std::endl;
						continue;
					default:
						break;
					}

					vec2 posI = (cam->mat * 
						colliders[i]->gameObject->transform->GetGlobalTransform()).c[2].xy;
					vec2 posO = (cam->mat * 
						colliders[o]->gameObject->transform->GetGlobalTransform()).c[2].xy;

					std::cout << "[WARNING - PHYSICS] Unhandled Collision: "
						<< std::endl
						<< i
						<< " "
						<< colliders[i]->gameObject->name
						<< " X: " << posI.x
						<< " Y: " << posI.y
						<< " AND "
						<< std::endl
						<< o
						<< " "
						<< colliders[o]->gameObject->name
						<< " X: " << posO.x
						<< " Y: " << posO.y
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
		else if ((colliders[i]->gameObject->tag.compare("null") == 0))
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

int Physics::isCollide(int i, int o, std::string tag)
{
	if (colliders[i]->gameObject->tag.compare(tag) == 0 && colliders[o]->gameObject->tag.compare(tag) == 0)
	{
		//std::cout << colliders[i]->gameObject->gameObject->tag << " " << colliders[o]->gameObject->gameObject->tag << " COLLISION" << std::endl;
		return 0;
	}
	return -1;
}
