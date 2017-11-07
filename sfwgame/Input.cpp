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
