#pragma once

union vec2;

float min(float a, float b);
float max(float a, float b);
vec2 min(vec2 a, vec2 b);
vec2 max(vec2 a, vec2 b);


float magnitude(const vec2 v);
vec2 normal(const vec2 v);
vec2 normalize(vec2 &v);
float dot(vec2 v1 , vec2 v2);
//Use this for two points
float distance(vec2 v1, vec2 v2);

//A from 0.0 to 1.0
vec2 lerp(vec2 start, vec2 end, float a);
