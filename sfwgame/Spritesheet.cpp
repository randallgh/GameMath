#include "Spritesheet.h"
#include "sfwdraw.h"
#include "mat3x3.h"


Spritesheet::Spritesheet(const char * path, int c, int r)
{
	handle = sfw::loadTextureMap(path, r, c);
	heightSpritesheet = sfw::getTextureHeight(handle);
	widthSpritesheet = sfw::getTextureWidth(handle);

	cols = c;
	rows = r;

	numSprites = cols * rows;

	widthSprite = widthSpritesheet / cols;
	heightSprite = heightSpritesheet / rows;
}

Spritesheet::~Spritesheet()
{

}

void Spritesheet::draw(mat3x3 transform, int index, float s, unsigned tint, float z)
{
	mat3x3 t = transform * scale(vec2{ s * widthSprite,s*heightSprite });
	sfw::drawTextureMatrix3(handle, index, tint, t.m, z);
}

int Spritesheet::GetNumSprites()
{
	return numSprites;
}
