#include "Input.h"
#include "sfwdraw.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"

Input::Input()
{
	GameObject * m = new GameObject();

	m->color = WHITE;
	m->isEnabled = true;

	SATGeometry mouseCollider =
	{
		{
			{ -0.5,-0.5 },
			{ 0.5,-0.5 },
			{ 0.5,0.5 },
			{ -0.5,0.5 }
		},
		4
	};

	m->collider = new Collider(mouseCollider, m, nullptr);
	m->transform = new Transform(m);

	mouse = m;
}


Input::~Input()
{

}

vec2 Input::getMousePos()
{
	return vec2{ sfw::getMouseX(), sfw::getMouseY() };
}

Collider Input::getMouseCollider()
{
	mouse->transform->position = getMousePos();
	return (*mouse->collider);
}

void Input::drawMouse()
{
	getMouseCollider().draw(mat3x3::identity());
}

bool Input::getMouseButtonDown(int button)
{
	if (sfw::getMouseButton(button))
	{
		switch (button)
		{
		case 0:
			if (isMouseLeftPressed)
			{
				return false;
			} 
			else 
			{
				isMouseLeftPressed = true;
				return true;
			}
		case 1:
			if (isMouseRightPressed)
			{

			}
			else
			{
				isMouseRightPressed = true;
			}
			return true;
		default:
			break;
		}
	}
	switch (button)
	{
	case 0:
		isMouseLeftPressed = false;
		break;
	case 1:
		isMouseRightPressed = false;
		break;
	default:
		break;
	}
	return false;
}
