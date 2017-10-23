#include "Hull.h"
#include "Transform.h"
#include "Collider.h"

Hull::Hull()
{
	tag = "hull";
	name = "null hull";
	isEnabled = false;

	transform = new Transform();
	collider = new Collider(this);
}


Hull::~Hull()
{

}

void Hull::update()
{

}

void Hull::draw()
{
	DrawMatrix(transform->GetGlobalTransform(), radius);
}
