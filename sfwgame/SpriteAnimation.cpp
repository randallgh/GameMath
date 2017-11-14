#include "SpriteAnimation.h"
#include "Spritesheet.h"
#include "mat3x3.h"



SpriteAnimation::SpriteAnimation(Spritesheet * sheet, float l)
{
	spritesheet = sheet;
	length = l;
}

SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::update(float dt)
{
	timer += dt;
	if (timer > length) { timer -= length; };
}

void SpriteAnimation::draw(mat3x3 transform, float s, unsigned tint, float z)
{
	int frameToDraw = spritesheet->GetNumSprites() * (timer / length);
	spritesheet->draw(transform, frameToDraw, s, tint, z);
}
