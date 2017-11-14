#include "Sprite.h"
#include "mat3x3.h"

Sprite::Sprite(const char * path)
{
	handle = sfw::loadTextureMap(path);
	width = sfw::getTextureWidth(handle);
	height = sfw::getTextureHeight(handle);
}

Sprite::~Sprite()
{

}

void Sprite::draw(mat3x3 transform, float s, unsigned tint, float z)
{
	mat3x3 t = transform * scale(vec2{ s * width, s * height });
	sfw::drawTextureMatrix3(handle, 0, tint, t.m, z);
}