#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"
#include "Rigidbody.h"

GameObject::GameObject()
{
	transform = nullptr;
	collider = nullptr;
	rigidbody = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	if (transform != nullptr) {

	}
	if (collider != nullptr) {

	}
	if (rigidbody != nullptr){
		rigidbody->update();
	}
}


