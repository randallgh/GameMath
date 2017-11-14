#pragma once
union mat3x3;

class Spritesheet
{
public:
	Spritesheet(const char * path, int c, int r);
	~Spritesheet();

	void draw(mat3x3 transform, int index, float s = 1.0f, unsigned tint = 0xfffffff, float z = 0.0f);
private:
	int cols;
	int rows;
	int numSprites;

	int widthSpritesheet;
	int heightSpritesheet;

	int widthSprite;
	int heightSprite;

	unsigned handle;
};

