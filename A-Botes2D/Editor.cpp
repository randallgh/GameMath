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
		editorState = EDITOR_MODES::HULL;
	}

	//Hull drawing mode
	//Left click to start placing X
	//Another click to place another point X
	//Right click to cancel last point and deselect hull drawing
	//Select Hull drawing again to be able to place more points
	//After drawing at least three points you can reconnet to the first point
	//Snapping to points placed (ajustable)
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
	case HULL:
		placeingPos = input->getMousePos();
		snapIndex = getClosestPoint(placeingPos);

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