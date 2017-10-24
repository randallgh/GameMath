#include "drawutils.h"

void drawVecLine(vec2 p1, vec2 p2, unsigned int tint)
{
	sfw::drawLine(p1.x, p1.y, p2.x, p2.y, tint);
	//sfw::drawLine3(p1.x, p1.y, p2.x, p2.y, 1, tint, transform);
}

void drawVecCircle(vec2 p, float radius, unsigned int steps, unsigned int tint)
{
	sfw::drawCircle(p.x, p.y, radius, steps, tint);
}
