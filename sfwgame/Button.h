#pragma once
#include "GameObject.h"

union mat3x3;
union vec2;

class Input;

class Button : public GameObject
{
public:
	Button(Input * i, float w, float h, vec2 pos);
	~Button();

	float isClicked;
	Input * input;

	void update(float dt);
	void draw(mat3x3 cam);

private:
	float width;
	float height;
};

