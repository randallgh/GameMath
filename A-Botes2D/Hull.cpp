#include "Hull.h"
#include "Transform.h"
#include "Collider.h"
#include "Physics.h"
#include "Ship.h"
#include "Rigidbody.h"

Hull::Hull(Physics * phys)
{
	tag = "Hull";
	name = "Hull";

	isEnabled = true;
	transform = new Transform();
	collider = new Collider(this, phys);
	rigidbody = new Rigidbody(this);
}


Hull::~Hull()
{

}

void Hull::update()
{
	if (parentShip == nullptr) { return; }
	isEnabled = parentShip->isEnabled;
}

void Hull::draw()
{

}
