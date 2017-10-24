#include "drawutils.h"

void drawVecLine(vec2 p1, vec2 p2, unsigned int tint, const float * transform)
{
	sfw::drawLine(p1.x, p1.y, p2.x, p2.y, tint);
	//sfw::drawLine3(p1.x, p1.y, p2.x, p2.y, 1, tint, transform);
}
