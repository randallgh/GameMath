#pragma once
#include "vec2.h"
#include "Screen.h"
#include <string>
#include "Collider.h"::SATGeometry

class Button;
class Input;
class Camera;

class Editor
{
public:
	Editor(Input * i, Camera * mC, unsigned * sBitmap);
	~Editor();

	ScreenInfo SCR_INFO;

	void update(float dt);
	
	Button * editorExitButton;
private:
	Input * input;
	Camera * mainCam;
	unsigned * stringBitmap;

	vec2 points[SATGeometry::MAX_POINTS] = {};
	int numPoints = 0;

	std::string shipName;

	int snapIndex;
	float hullDrawSnapRadius = 25;
	bool isSnapping = false;

	vec2 placeingPos;

	enum EDITOR_MODES
	{
		IDLE,
		HULLDRAW,
		EDIT
	};

	EDITOR_MODES editorState = EDITOR_MODES::IDLE;

	void hullDraw();

	int getClosestPoint(vec2 pos);

	bool saveShip(std::string shipN);
	bool loadShip(std::string shipN);
};

