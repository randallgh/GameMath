#include "NavalBattery.h"
#include "Transform.h"
#include "Ship.h"
#include "Camera.h"

NavalBattery::NavalBattery(vec2 pos)
{
	transform = new Transform();
}

NavalBattery::~NavalBattery()
{
}

void NavalBattery::update()
{

}

void NavalBattery::draw()
{
	DrawMatrix(parentShip->cam->mat * transform->GetGlobalTransform(), 10);
}
