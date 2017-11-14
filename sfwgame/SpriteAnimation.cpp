#include "SpriteAnimation.h"
#include "mat3x3.h"

SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::update(float dt)
{
	timer += dt;
}

void SpriteAnimation::draw(mat3x3 transform)
{
	int frameToDraw = numFrames * (timer / length);
	frames[frameToDraw]->draw(transform, 1, WHITE, 0);
}
