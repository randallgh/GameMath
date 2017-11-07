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

Button::~Button()
{
	delete transform;
	delete collider;
}

void Button::update(float dt)
{
	if (!isEnabled) { return; }

	if (input->getMouseCollider().doesCollide(collider).penetration > 0)
	{
		color = RED;
	}
	else
	{
		color = YELLOW;
	}

}

void Button::draw(mat3x3 cam)
{
	if (!isEnabled) { return; }
	collider->draw(cam);
}
