#pragma once


float dbl(float v);
float sqr(float v);
float cube(float v);
float degToRad(float deg);
float radToDeg(float rad);

float distance(float x1, float y1, float x2, float y2);

//http://cubic-bezier.com
float cubicBezier(float time, float p1, float p2, float p3, float p4);