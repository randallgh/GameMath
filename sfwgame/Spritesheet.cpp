#include "Spritesheet.h"
#include "sfwdraw.h"
#include "mat3x3.h"

#include <cassert>


Spritesheet::Spritesheet(const char * path, int c, int r)
{
	_handle = sfw::loadTextureMap(path, r, c);
	_heightSpritesheet = sfw::getTextureHeight(_handle);
	_widthSpritesheet = sfw::getTextureWidth(_handle);

	//assert(_heightSpritesheet == 0);
	//assert(_widthSpritesheet == 0);

	_cols = c;
	_rows = r;

	_numSprites = _cols * _rows;

	_widthSprite = _widthSpritesheet / _cols;
	_heightSprite = _heightSpritesheet / _rows;
}

Spritesheet::~Spritesheet()
{

}

void Spritesheet::draw(mat3x3 transform, int index, float s, unsigned tint, float z)
{
	mat3x3 t = transform * scale(vec2{ s * _widthSprite,s*_heightSprite });
	sfw::drawTextureMatrix3(_handle, index, tint, t.m, z);
}

void Spritesheet::draw(vec2 pos, int index, float s, unsigned tint, float z, SpriteDrawState drawState)
{
	mat3x3 t;
	switch (drawState)
	{
	case CENTER:
		t = translate(pos) * scale(vec2{ s * _widthSprite,s*_heightSprite });
		sfw::drawTextureMatrix3(_handle, index, tint, t.m, z);
		break;
	case BOTTOM_LEFT:
		t = translate(pos + vec2{_widthSprite/2.0f,_heightSprite/2.0f}) * 
			scale(vec2{ s * _widthSprite,s*_heightSprite });
		sfw::drawTextureMatrix3(_handle, index, tint, t.m, z);
		break;
	default:
		break;
	}
}

int Spritesheet::GetNumSprites()
{
	return _numSprites;
}

int Spritesheet::GetSpriteWidth()
{
	return _widthSprite;
}

int Spritesheet::GetSpriteHeight()
{
	return _heightSprite;
}
