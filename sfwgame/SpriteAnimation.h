#pragma once
#include "Sprite.h"
class Spritesheet;

class SpriteAnimation
{
public:
	SpriteAnimation(Spritesheet sheet, float l);
	~SpriteAnimation();

	static const int MAX_FRAMES = 32;

	void update(float dt);
	void draw(mat3x3 transform);

private:
	int numFrames;
	Sprite ** frames;

	//Length in time
	float length;

	float timer;
};

