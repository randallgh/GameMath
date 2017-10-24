#pragma once

#include "sfwdraw.h"
#include "vec2.h"

void drawVecLine(vec2 p1,vec2 p2,unsigned int tint = WHITE);
void drawVecCircle(vec2 p, float radius, unsigned int steps = 12, unsigned int tint = WHITE);