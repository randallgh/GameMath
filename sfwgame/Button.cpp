#include "Button.h"
#include "mat3x3.h"
#include "vec2.h"

#include "Input.h"
#include "Transform.h"
#include "Collider.h"


#include "sfwdraw.h"
#include "drawutils.h"

Button::Button(Input * i, float w, float h, vec2 pos)
{
	input = i;
	width = w;
	height = h;
	color = WHITE;

	float w2 = width / 2;
	float h2 = height / 2;

	SATGeometry geo =
	{
		{
			{ -w2,-h2 } ,{ w2,-h2 },{ w2,h2 },{ -w2,h2 }
		},
		4
	};

	if (transform == nullptr){ transform = new Transform(this); }
	transform->position = pos;
	if (collider == nullptr) { collider = new Collider(geo, this, nullptr); }

	collider->geometry = geo;

	isEnabled = true;
}

Button::Button(Input * i, float w, float h, vec2 pos, std::string n)
{
	input = i;
	width = w;
	height = h;
	color = WHITE;
	name = n;

	float w2 = width / 2;
	float h2 = height / 2;

	SATGeometry geo =
	{
		{
			{ -w2,-h2 } ,{ w2,-h2 },{ w2,h2 },{ -w2,h2 }
		},
		4
	};

	if (transform == nullptr) { transform = new Transform(this); }
	transform->position = pos;
	if (collider == nullptr) { collider = new Collider(geo, this, nullptr); }

	collider->geometry = geo;

	isEnabled = true;
}

Button::~Button()
{
	delete transform;
	delete collider;
}

void Button::update(float dt)
{
	if (!isEnabled) { return; }

	if (input->getMouseCollider().doesCollide(this->collider).penetration > 0)
	{
		if (isClicked) { isClicked = false; }
		if (sfw::getMouseButton(0))
		{
			isClicked = true;
		}
		color = RED;
	}
	else
	{
		isClicked = false;
		color = YELLOW;
	}

}

void Button::draw(mat3x3 cam)
{
	if (!isEnabled) { return; }
	collider->draw(cam * transform->GetGlobalTransform());
}

void Button::draw(mat3x3 cam, unsigned stringBitmap)
{
	if (!isEnabled) { return; }
	mat3x3 mat = cam * transform->GetGlobalTransform();

	collider->draw(mat);
	sfw::drawString(stringBitmap, name.c_str(), mat.c[2].xy.x - (width / 2), mat.c[2].xy.y + (height / 2), width, height, 0,'\000', color);
}
