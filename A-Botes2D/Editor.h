#pragma once
#include "vec2.h"
#include "Screen.h"
class Button;
class Input;
class Camera;

class Editor
{
public:
	Editor(Input * i, Camera * mC, unsigned * sBitmap);
	~Editor();

	Button * editorExitButton;
	Input * input;
	Camera * mainCam;
	unsigned * stringBitmap;

	vec2 points[16] = {};
	int numPoints = 0;

	int snapIndex;
	float hullDrawSnapRadius = 25;
	bool isSnapping = false;

	vec2 placeingPos;

	ScreenInfo SCR_INFO;
	enum EDITOR_MODES
	{
		IDLE,
		HULL
	};

	EDITOR_MODES editorState = EDITOR_MODES::IDLE;

	void update(float dt);

	int getClosestPoint(vec2 pos);
};

