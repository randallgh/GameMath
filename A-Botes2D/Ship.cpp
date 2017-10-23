#include "Ship.h"
#include "Hull.h"
#include "vec2.h"

Ship::Ship()
{
}

Ship::Ship( Hull * h, int hc)
{
	hull = h;
	HULL_COUNT = hc;
}

Ship::~Ship()
{
}

void Ship::update()
{
}

void Ship::draw()
{
}
