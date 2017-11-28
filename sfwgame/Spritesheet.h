#pragma once
union mat3x3;
union vec2;

class Spritesheet
{
public:

	static enum SpriteDrawState
	{
		CENTER,
		BOTTOM_LEFT
	};

	Spritesheet(const char * path, int c, int r);
	~Spritesheet();

	void draw(mat3x3 transform, int index, float s = 1.0f, unsigned tint = 0xfffffff, float z = 0.0f);
	void draw(vec2 pos, int index, float s = 1.0f, 
		unsigned tint = 0xfffffff, float z = 0.0f, SpriteDrawState drawState = CENTER);
	int GetNumSprites();

	int GetSpriteWidth();
	int GetSpriteHeight();
private:
	int _cols;
	int _rows;
	int _numSprites;

	int _widthSpritesheet;
	int _heightSpritesheet;

	int _widthSprite;
	int _heightSprite;

	unsigned _handle;
};

