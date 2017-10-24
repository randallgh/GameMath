#include "Input.h"
#include "sfwdraw.h"


Input::Input()
{
}


Input::~Input()
{
}

vec2 Input::getMousePos()
{
	return vec2{ sfw::getMouseX(), sfw::getMouseY() };
}
