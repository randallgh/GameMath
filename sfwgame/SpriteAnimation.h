#pragma once
#include "Sprite.h"
class Spritesheet;

class SpriteAnimation
{
public:
	SpriteAnimation(Spritesheet * sheet, float l);
	~SpriteAnimation();

	static const int MAX_FRAMES = 32;

	void update(float dt);
	void draw(mat3x3 transform, float s = 1.0f, unsigned tint = 0xfffffff, float z = 0.0f);

private:
	int numFrames;
	Sprite ** frames;
	Spritesheet * spritesheet;

	//Length in time
	float length;

	float timer;
};

