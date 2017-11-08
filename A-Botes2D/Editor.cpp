#include "Editor.h"
#include "Button.h"
#include "Input.h"
#include "mat3x3.h"
#include "sfwdraw.h"
#include "Camera.h"
#include "drawutils.h"

#include <iostream>
#include <fstream>

Editor::Editor(Input * i, Camera * mC, unsigned * sBitmap)
{
	input = i;
	mainCam = mC;
	stringBitmap = sBitmap;

	editorExitButton = new Button(i, 50, 50, vec2{ 25, (float)SCR_INFO.SCR_HEIGHT - 25 }, "Exit");
}


Editor::~Editor()
{
}

void Editor::update(float dt)
{
	mainCam->mat = mat3x3::identity();

	if (sfw::getKey(KEY_H))
	{
		editorState = EDITOR_MODES::HULLDRAW;
	}

	//Hull drawing mode X
	//Left click to start placing X
	//Another click to place another point X
	//Right click to cancel last point and deselect hull drawing X
	//Select Hull drawing again to be able to place more points X
	//After drawing at least three points you can reconnet to the first point x
	//Snapping to points placed (ajustable) X
	//Snapping mode to a grid (ajustable)
	//Hold shift to snap to 45degree
	//Another mode to display the cords of the points and click to edit

	//getclosestpoint

	switch (editorState)
	{
	case IDLE:

		for (int i = 0; i < numPoints && numPoints >= 1; ++i)
		{
			drawVecLine(points[i], points[(i + 1) % numPoints], WHITE);
		}

		if (sfw::getKey(KEY_ENTER) && numPoints > 2)
		{
			saveShip("test");
			saveAkizuki();
		}

		if (sfw::getKey(KEY_L))
		{
			loadShip("test");
		}

		break;
	case HULLDRAW:
		hullDraw();
		break;
	default:
		break;
	}

	editorExitButton->draw(mainCam->mat, *stringBitmap);
	editorExitButton->update(dt);
}

void Editor::hullDraw()
{
	sfw::drawLine(0, SCR_INFO.SCR_HEIGHT / 2, SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT / 2, RED);
	sfw::drawLine(SCR_INFO.SCR_WIDTH / 2, SCR_INFO.SCR_HEIGHT, SCR_INFO.SCR_WIDTH / 2, 0, GREEN);

	placeingPos = input->getMousePos();
	snapIndex = getClosestPoint(placeingPos);

	//Holding shift
	if (sfw::getKey(KEY_LEFT_SHIFT) && (numPoints > 0))
	{
		float x = points[numPoints - 1].x - placeingPos.x;
		float y = points[numPoints - 1].y - placeingPos.y;
		vec2 vec = { x,y };

		float deg = (int)VectorToDegree(vec2{ abs(vec.x),abs(vec.y) }) % 360;

		if (deg > 45 && deg < 135 || deg > 225 && deg < 270)
		{
			placeingPos = points[numPoints - 1] - vec2{ 0,vec.y };
		}
		else { placeingPos = points[numPoints - 1] - vec2{ vec.x,0 }; }
	}

	//Snapping
	if (snapIndex >= 0 && numPoints > 2)
	{
		placeingPos = points[snapIndex];
		isSnapping = true;
	}
	else
	{
		isSnapping = false;
	}

	//On left click
	if (input->getMouseButtonDown(0) && (numPoints < SATGeometry::MAX_POINTS) 
		|| input->getMouseButtonDown(0) && isSnapping)
	{
		if (isSnapping)
		{
			//End placing points
			editorState = EDITOR_MODES::IDLE;
			return;
		}

		points[numPoints] = placeingPos;
		numPoints++;
	}

	//On right click
	if (input->getMouseButtonDown(1))
	{
		if (numPoints > 0) { numPoints--; }
	}

	//On G press
	if (input->getKeyDown('G'))
	{
		isGridActive = !isGridActive;
	}

	//Render Grid
	if (isGridActive)
	{
		for (int i = 1; i < gridCols; ++i)
		{
			if ((((float)SCR_INFO.SCR_WIDTH / gridCols) * i) == ((float)SCR_INFO.SCR_WIDTH/2)){continue; }
			drawVecLine(vec2{ ((float)SCR_INFO.SCR_WIDTH / gridCols) * i, 0 },
				vec2{ ((float)SCR_INFO.SCR_WIDTH / gridCols) * i, (float)SCR_INFO.SCR_HEIGHT }, WHITE);
		}
		for (int i = 0; i < gridRows; ++i)
		{
			if ((((float)SCR_INFO.SCR_HEIGHT / gridRows) * i) == ((float)SCR_INFO.SCR_HEIGHT / 2)) { continue; }
			drawVecLine(vec2{ 0,						 ((float)SCR_INFO.SCR_HEIGHT / gridRows) * i },
				vec2{ (float)SCR_INFO.SCR_WIDTH, ((float)SCR_INFO.SCR_HEIGHT / gridRows) * i }, WHITE);
		}
	}

	//Render Hull
	for (int i = 0; i < numPoints && numPoints >= 1; ++i)
	{
		if (i == (numPoints - 1))
		{
			drawVecLine(points[i], placeingPos, RED);
		}
		else
		{
			drawVecLine(points[i], points[(i + 1) % numPoints], WHITE);
		}
	}
}

int Editor::getClosestPoint(vec2 pos)
{
	for (int i = 0; i < numPoints; ++i)
	{
		if (distance(points[i], pos) < hullDrawSnapRadius && i != numPoints - 1)
		{
			return i;
		}
	}

	return -1;
}

bool Editor::saveShip(std::string shipN)
{
	std::ofstream file;
	std::string destinationName = "data/ships/" + shipN + ".txt";
	file.open(destinationName);

	file << "@Ship" << "\n";
	file << shipN << "\n";

	file << "@Hull" << "\n";
	file << numPoints << "\n";

	for (int i = 0; i < numPoints; ++i)
	{
		file << points[i].x - (SCR_INFO.SCR_WIDTH / 2) << "\n";
		file << points[i].y - (SCR_INFO.SCR_HEIGHT / 2)<< "\n";
	}

	file.flush();
	file.close();
	return true;
}

bool Editor::loadShip(std::string shipN)
{
	std::ifstream file;
	std::string destinationName = "data/ships/" + shipN + ".txt";
	std::string buffer;
	file.open(destinationName);

	if (!file.fail())
	{
		std::getline(file, buffer);
		if (buffer.compare("@Ship") == 0)
		{
			std::getline(file, buffer);
			shipName = buffer;
		}
		else { return false; }

		std::getline(file, buffer);
		if (buffer.compare("@Hull") == 0)
		{
			std::getline(file, buffer);
			numPoints = std::stoi(buffer);

			for (int i = 0; i < numPoints; ++i)
			{
				std::getline(file, buffer);
				points[i].x = std::stof(buffer) + (SCR_INFO.SCR_WIDTH / 2);
				std::getline(file, buffer);
				points[i].y = std::stof(buffer) + (SCR_INFO.SCR_HEIGHT / 2);
			}
		}
		else { return false; }

		file.close();
		return true;
	}

	return false;
}

void Editor::saveAkizuki()
{
	float length = 440;
	float width = 38;
	float length2 = length / 2;
	float width2 = width / 2;
	SATGeometry col =
	{
		{
			{ -length2 + 20, width2 },
			{ -length2, width / 4 },
			{ -length2, -width / 4 },
			{ -length2 + 20, -width2 },
			{ length / 4,-width2 },
			{ length2,-2 },
			{ length2,2 },
			{ length / 4,width2 },

		},
		8
	};

	std::ofstream file;
	std::string destinationName = "data/ships/Akizuki.txt";
	file.open(destinationName);

	file << "@Ship" << "\n";
	file << "Akizuki" << "\n";

	file << "@Hull" << "\n";
	file << col.numPoints << "\n";

	for (int i = 0; i < col.numPoints; ++i)
	{
		file << col.points[i].x << "\n";
		file << col.points[i].y << "\n";
	}

	file.flush();
	file.close();
	return;
}


