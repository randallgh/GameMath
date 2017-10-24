#include "Hull.h"
#include "Transform.h"
#include "Collider.h"
#include "Physics.h"

Hull::Hull(Physics * phys)
{
	tag = "Hull";
	name = "Hull";

	isEnabled = true;
	transform = new Transform();
	collider = new Collider(this, phys);
}


Hull::~Hull()
{

}

void Hull::update()
{

}

void Hull::draw()
{
}
