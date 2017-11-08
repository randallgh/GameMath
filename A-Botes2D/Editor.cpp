#include "Editor.h"
#include "Button.h"
#include "Input.h"
#include "mat3x3.h"
#include "sfwdraw.h"
#include "Camera.h"
#include "drawutils.h"
#include "GameManager.h"

#include <iostream>
#include <fstream>

Editor::Editor(Input * i, Camera * mC, unsigned * sBitmap, GameManager * gM)
{
	input = i;
	mainCam = mC;
	stringBitmap = sBitmap;
	gameManager = gM;

	exitButton = new Button(i, 50, 50, vec2{ 25, (float)SCR_INFO.SCR_HEIGHT - 25 }, "Exit");
	hullEditButton = new Button(i, 50, 50, vec2{ (float)SCR_INFO.SCR_WIDTH - 25, (float)SCR_INFO.SCR_HEIGHT - 25 }, "H");
	mainBatteryEditButton = new Button(i, 50, 50, vec2{ (float)SCR_INFO.SCR_WIDTH - 25, (float)SCR_INFO.SCR_HEIGHT - 75 }, "G");
	torpedoTubeEditButton = new Button(i, 50, 50, vec2{ (float)SCR_INFO.SCR_WIDTH - 25, (float)SCR_INFO.SCR_HEIGHT - 125 }, "T");
}


Editor::~Editor()
{
}

void Editor::update(float dt)
{
	mainCam->mat = mat3x3::identity();

	if (input->getKeyDown(KEY_H))
	{
		if (editorState == EDITOR_MODES::HULLDRAW)
		{
			editorState = EDITOR_MODES::IDLE;
		}
		else
		{
			editorState = EDITOR_MODES::HULLDRAW;
		}
		
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
			if ((((float)SCR_INFO.SCR_WIDTH / gridCols) * i) == ((float)SCR_INFO.SCR_WIDTH / 2)) { continue; }
			drawVecLine(vec2{ ((float)SCR_INFO.SCR_WIDTH / gridCols) * i, 0 },
				vec2{ ((float)SCR_INFO.SCR_WIDTH / gridCols) * i, (float)SCR_INFO.SCR_HEIGHT }, WHITE);
		}
		for (int i = 0; i < gridRows; ++i)
		{
			if ((((float)SCR_INFO.SCR_HEIGHT / gridRows) * i) == ((float)SCR_INFO.SCR_HEIGHT / 2)) { continue; }
			drawVecLine(vec2{ 0,						 ((float)SCR_INFO.SCR_HEIGHT / gridRows) * i },
				vec2{ (float)SCR_INFO.SCR_WIDTH, ((float)SCR_INFO.SCR_HEIGHT / gridRows) * i }, WHITE);
		}
		sfw::drawLine(0, SCR_INFO.SCR_HEIGHT / 2, SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT / 2, RED);
		sfw::drawLine(SCR_INFO.SCR_WIDTH / 2, SCR_INFO.SCR_HEIGHT, SCR_INFO.SCR_WIDTH / 2, 0, GREEN);
	}

	sfw::drawString(*stringBitmap, editorStatus.c_str(), 25, 25, 25, 25, 0, '\000', WHITE);


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

	if (sfw::getKey(KEY_ENTER) && numHullPoints > 2)
	{
		saveShip("test");
		saveAkizuki();
	}

	//On S press
	if (input->getKeyDown('S'))
	{
		canSnap = !canSnap;
	}

	exitButton->update(dt);
	hullEditButton->update(dt);
	mainBatteryEditButton->update(dt);
	torpedoTubeEditButton->update(dt);

	if (hullEditButton->isClicked)
	{
		editorState = EDITOR_MODES::HULLDRAW;
	}

	if (mainBatteryEditButton->isClicked)
	{
		editorState = EDITOR_MODES::MAINBATTERY;
	}

	if (torpedoTubeEditButton->isClicked)
	{
		editorState = EDITOR_MODES::TORPEDOTUBES;
	}

	if (exitButton->isClicked) 
	{ 
		gameManager->pState = PROGRAM_STATE::_MAINMENU_;
		return;
	}

	switch (editorState)
	{
	case IDLE:
		displayShip();
		if (sfw::getKey(KEY_L))
		{
			loadShip("test");
		}
		editorStatus = "Idle";
		break;
	case HULLDRAW:
		hullDraw();
		editorStatus = "Hull Draw";
		break;
	case MAINBATTERY:
		displayShip();
		mainGuns();
		editorStatus = "Main Battery placement";
		break;
	case TORPEDOTUBES:
		displayShip();
		torpedoTubes();
		editorStatus = "Torpedo Tube placement";
		break;
	default:
		break;
	}

	exitButton->draw(mainCam->mat, *stringBitmap);
	hullEditButton->draw(mainCam->mat, *stringBitmap);
	mainBatteryEditButton->draw(mainCam->mat, *stringBitmap);
	torpedoTubeEditButton->draw(mainCam->mat, *stringBitmap);
}

void Editor::hullDraw()
{

	placeingPos = input->getMousePos();
	snapIndex = getClosestPoint(placeingPos);

	//Holding shift
	if (sfw::getKey(KEY_LEFT_SHIFT) && (numHullPoints > 0))
	{
		float x = hullPoints[numHullPoints - 1].x - placeingPos.x;
		float y = hullPoints[numHullPoints - 1].y - placeingPos.y;
		vec2 vec = { x,y };

		float deg = (int)VectorToDegree(vec2{ abs(vec.x),abs(vec.y) }) % 360;

		if (deg > 45 && deg < 135 || deg > 225 && deg < 270)
		{
			placeingPos = hullPoints[numHullPoints - 1] - vec2{ 0,vec.y };
		}
		else { placeingPos = hullPoints[numHullPoints - 1] - vec2{ vec.x,0 }; }
	}

	//Snapping
	if (snapIndex >= 0 && numHullPoints > 2 && canSnap)
	{
		placeingPos = hullPoints[snapIndex];
		isSnapping = true;
	}
	else
	{
		isSnapping = false;
	}

	//On left click
	if (input->getMouseButtonDown(0) && (numHullPoints < SATGeometry::MAX_POINTS) && !hullEditButton->isClicked
		|| input->getMouseButtonDown(0) && isSnapping)
	{
		if (isSnapping)
		{
			//End placing points
			editorState = EDITOR_MODES::IDLE;
			return;
		}

		hullPoints[numHullPoints] = placeingPos;
		numHullPoints++;
	}

	//On right click
	if (input->getMouseButtonDown(1))
	{
		if (numHullPoints > 0) { numHullPoints--; }
	}

	//Render Hull
	for (int i = 0; i < numHullPoints && numHullPoints >= 1; ++i)
	{
		if (i == (numHullPoints - 1))
		{
			drawVecLine(hullPoints[i], placeingPos, RED);
		}
		else
		{
			drawVecLine(hullPoints[i], hullPoints[(i + 1) % numHullPoints], WHITE);
		}
	}
}

void Editor::mainGuns()
{
	if (input->getMouseButtonDown(0) && (numMainGuns < MAX_MAIN_BATTRIES) && !mainBatteryEditButton->isClicked)
	{
		mainBatteryPoints[numMainGuns] = input->getMousePos();
		numMainGuns++;
	}
	if (input->getMouseButtonDown(1) && (numMainGuns > 0) && !mainBatteryEditButton->isClicked)
	{
		numMainGuns--;
	}
}

void Editor::torpedoTubes()
{
	if (input->getMouseButtonDown(0) && (numTorpedoTubes < MAX_TORPEDO_TUBES) && !torpedoTubeEditButton->isClicked)
	{
		torpedoTubePoints[numTorpedoTubes] = input->getMousePos();
		numTorpedoTubes++;
	}
	if (input->getMouseButtonDown(1) && (numTorpedoTubes > 0) && !torpedoTubeEditButton->isClicked)
	{
		numTorpedoTubes--;
	}
}

void Editor::displayShip()
{
	for (int i = 0; i < numHullPoints && numHullPoints >= 1; ++i)
	{
		drawVecLine(hullPoints[i], hullPoints[(i + 1) % numHullPoints], WHITE);
	}

	for (int i = 0; i < numMainGuns; i++)
	{
		drawVecCircle(mainBatteryPoints[i], 4, 12, RED);
	}

	for (int i = 0; i < numTorpedoTubes; i++)
	{
		drawVecCircle(torpedoTubePoints[i], 4, 12, BLUE);
	}

}

int Editor::getClosestPoint(vec2 pos)
{
	for (int i = 0; i < numHullPoints; ++i)
	{
		if (distance(hullPoints[i], pos) < hullDrawSnapRadius && i != numHullPoints - 1)
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
	file << numHullPoints << "\n";

	for (int i = 0; i < numHullPoints; ++i)
	{
		file << hullPoints[i].x - (SCR_INFO.SCR_WIDTH / 2) << "\n";
		file << hullPoints[i].y - (SCR_INFO.SCR_HEIGHT / 2)<< "\n";
	}

	file << "@MainGuns" << "\n";
	file << numMainGuns << "\n";

	for (int i = 0; i < numMainGuns; i++)
	{
		file << mainBatteryPoints[i].x - (SCR_INFO.SCR_WIDTH / 2) << "\n";
		file << mainBatteryPoints[i].y - (SCR_INFO.SCR_HEIGHT / 2) << "\n";
	}

	file << "@TorpedoTubes" << "\n";
	file << numTorpedoTubes << "\n";

	for (int i = 0; i < numTorpedoTubes; i++)
	{
		file << torpedoTubePoints[i].x - (SCR_INFO.SCR_WIDTH / 2) << "\n";
		file << torpedoTubePoints[i].y - (SCR_INFO.SCR_HEIGHT / 2) << "\n";
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
			numHullPoints = std::stoi(buffer);

			for (int i = 0; i < numHullPoints; ++i)
			{
				std::getline(file, buffer);
				hullPoints[i].x = std::stof(buffer) + (SCR_INFO.SCR_WIDTH / 2);
				std::getline(file, buffer);
				hullPoints[i].y = std::stof(buffer) + (SCR_INFO.SCR_HEIGHT / 2);
			}
		}
		else { return false; }

		std::getline(file, buffer);
		if (buffer.compare("@MainGuns") == 0)
		{
			std::getline(file, buffer);
			numMainGuns = std::stoi(buffer);

			for (int i = 0; i < numMainGuns; ++i)
			{
				std::getline(file, buffer);
				mainBatteryPoints[i].x = std::stof(buffer) + (SCR_INFO.SCR_WIDTH / 2);
				std::getline(file, buffer);
				mainBatteryPoints[i].y = std::stof(buffer) + (SCR_INFO.SCR_HEIGHT / 2);
			}
		}

		std::getline(file, buffer);
		if (buffer.compare("@TorpedoTubes") == 0)
		{
			std::getline(file, buffer);
			numTorpedoTubes = std::stoi(buffer);

			for (int i = 0; i < numTorpedoTubes; ++i)
			{
				std::getline(file, buffer);
				torpedoTubePoints[i].x = std::stof(buffer) + (SCR_INFO.SCR_WIDTH / 2);
				std::getline(file, buffer);
				torpedoTubePoints[i].y = std::stof(buffer) + (SCR_INFO.SCR_HEIGHT / 2);
			}
		}

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

	int hullNum = 1;
	int const mainGunNum = 4;
	int const torpedoMountsNum = 1;

	vec2 mG[mainGunNum] = { { 100 + 30,0 } ,{ 100 ,0 },{ -100,0 },{ -100 - 30,0 } };
	vec2 tM[torpedoMountsNum] = { { -50,0 } };

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


	file << "@MainGuns" << "\n";
	file << mainGunNum << "\n";

	for (int i = 0; i < mainGunNum; i++)
	{
		file << mG[i].x << "\n";
		file << mG[i].y << "\n";
	}

	file << "@TorpedoTubes" << "\n";
	file << torpedoMountsNum << "\n";

	for (int i = 0; i < torpedoMountsNum; i++)
	{
		file << tM[i].x << "\n";
		file << tM[i].y << "\n";
	}

	file.flush();
	file.close();
	return;
}


