#pragma once

#include "vec2.h"

class Player
{
public:
	Player();
	~Player();

	vec2 position;
	vec2 velocity;
	vec2 acceleration;

	float mass;

	void draw();
	void update();
};

