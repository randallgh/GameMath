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
	
	Button * exitButton;
	Button * hullEditButton;
	Button * mainBatteryEditButton;
	Button * torpedoTubeEditButton;

private:

	std::string editorStatus = "Idle";

	Input * input;
	Camera * mainCam;
	unsigned * stringBitmap;

	static const size_t MAX_TORPEDO_TUBES = 16;
	static const size_t MAX_MAIN_BATTRIES = 16;

	vec2 hullPoints[SATGeometry::MAX_POINTS] = {};
	vec2 mainBatteryPoints[MAX_MAIN_BATTRIES] = {};
	vec2 torpedoTubePoints[MAX_TORPEDO_TUBES] = {};

	int numPoints = 0;
	int numMainGuns = 0;
	int numTorpedoTubes = 0;

	std::string shipName;

	int snapIndex;
	float hullDrawSnapRadius = 25;
	bool isSnapping = false;

	vec2 placeingPos;

	int gridCols = 10;
	int gridRows = 10;
	bool isGridActive = false;
	bool canSnap = false;

	enum EDITOR_MODES
	{
		IDLE,
		HULLDRAW,
		MAINBATTERY,
		TORPEDOTUBES,
		EDIT
	};

	EDITOR_MODES editorState = EDITOR_MODES::IDLE;

	void hullDraw();
	void mainGuns();
	void torpedoTubes();


	void displayShip();

	int getClosestPoint(vec2 pos);

	bool saveShip(std::string shipN);
	bool loadShip(std::string shipN);

	void saveAkizuki();
};

