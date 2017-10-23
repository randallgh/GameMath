#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"

GameObject::GameObject()
{
	transform = nullptr;
	collider = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	if (transform != nullptr) {

	}
	if (collider != nullptr) {
		collider->update();
	}
}


