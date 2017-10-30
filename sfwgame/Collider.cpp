#include "Collider.h"
#include "Transform.h"
#include "sfwdraw.h"
#include "Physics.h"
#include "GameObject.h"

Collider::Collider(GameObject * go, Physics * phys)
{
	type = ColliderType::Circle;

	gameObject = go;

	phys->addCollider(this);
}

Collider::~Collider()
{
}

//void Collider::update()
//{
//	if (this == nullptr) { return; }
//	if (!gameObject->isEnabled) { return; }
//	gameObject->transform->position += velocity * sfw::getDeltaTime();
//}
//
//void Collider::draw()
//{
//
//}
