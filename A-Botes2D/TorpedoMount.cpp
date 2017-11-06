#include "TorpedoMount.h"

#include "sfwdraw.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "drawutils.h"


#include "Torpedo.h"

#include <iostream>

TorpedoMount::TorpedoMount(Physics * phys, const vec2 & pos)
{
	isEnabled = true;
	transform = new Transform(this);
	rigidbody = new Rigidbody(this);

	transform->position = pos;

	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		torpedos[i] = nullptr;
	}
}


TorpedoMount::~TorpedoMount()
{

}

void TorpedoMount::update(float dt)
{

	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		if (torpedos[i] == nullptr) { continue; }
		torpedos[i]->update(dt);
	}
}

void TorpedoMount::draw(mat3x3 cam)
{
	DrawMatrix(cam * transform->GetGlobalTransform(), 20);
	drawVecCircle((cam * transform->GetGlobalTransform()).c[2].xy, 10, 12, RED);

	for (int i = 0; i < MAX_TORPEDOES; ++i)
	{
		if (torpedos[i] == nullptr) { continue; }
		torpedos[i]->draw(cam);
	}
}
