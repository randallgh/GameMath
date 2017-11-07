#pragma once
#include "GameObject.h"

union mat3x3;
union vec2;

class Input;

class Button : public GameObject
{
public:
	Button(Input * i, float w, float h, vec2 pos);
	Button(Input * i, float w, float h, vec2 pos, std::string n);
	~Button();

	float isClicked;
	Input * input;

	void update(float dt);
	void draw(mat3x3 cam);
	void draw(mat3x3 cam, unsigned stringBitmap);

private:
	float width;
	float height;
};

