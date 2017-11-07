#include "Editor.h"
#include "Button.h"
#include "Input.h"
#include "mat3x3.h"
#include "sfwdraw.h"
#include "Camera.h"
#include "drawutils.h"

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

		break;
	case HULLDRAW:

		placeingPos = input->getMousePos();
		snapIndex = getClosestPoint(placeingPos);

		//Holding shift
		if (sfw::getKey(KEY_LEFT_SHIFT) && (numPoints > 0))
		{
			float x = points[numPoints - 1].x - placeingPos.x;
			float y = points[numPoints - 1].y - placeingPos.y;
			vec2 vec = {x,y};

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
		if (input->getMouseButtonDown(0) && (numPoints <= 15))
		{
			points[numPoints] = placeingPos;
			numPoints++;

			if (isSnapping)
			{
				//End placing points
				editorState = EDITOR_MODES::IDLE;
			}
		}

		//On right click
		if (input->getMouseButtonDown(1))
		{
			editorState = EDITOR_MODES::IDLE;
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
		break;
	default:
		break;
	}

	editorExitButton->draw(mainCam->mat, *stringBitmap);
	editorExitButton->update(dt);
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

bool Editor::saveShip()
{

	return false;
}
