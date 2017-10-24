#include "NavalBattery.h"
#include "Transform.h"
#include "Ship.h"
#include "Camera.h"
#include "sfwdraw.h"
#include "Shell.h"
#include "Collider.h"

NavalBattery::NavalBattery(vec2 pos, float reload)
{
	isEnabled = true;
	transform = new Transform();

	reloadTime = reload;
	reloadTimer = 0;

	for (int i = 0; i < MAX_SHELLS; ++i) 
	{
		shells[i] = nullptr;
	}
}

NavalBattery::~NavalBattery()
{
}

void NavalBattery::update()
{
	if (!isEnabled) { return; }
	reloadTimer += sfw::getDeltaTime();


}

void NavalBattery::draw()
{
	DrawMatrix(parentShip->cam->mat * transform->GetGlobalTransform(), 10);
	for (int i = 0; i < MAX_SHELLS; ++i) 
	{
		if (shells[i] == nullptr) { continue; }
		shells[i]->draw();
	}
}

void NavalBattery::shoot(vec2 pos)
{
	if (reloadTimer >= reloadTime) 
	{
		Shell * shell = findNextShell();
		if (shell == nullptr) 
		{
			shell = new Shell();
		}
		shell->setupShell(shellType1);
		shell->reset();
		shell->collider->velocity =
			normal(transform->GetGlobalTransform().c[2].xy - pos) * shell->speed;
	}
}

Shell * NavalBattery::findNextShell()
{
	for (int i = 0; i < MAX_SHELLS; ++i) 
	{
		if (nullptr) 
		{
			return shells[i];
		}
		if (!shells[i]->isEnabled) 
		{
			return shells[i];
		}
	}
	return nullptr;
}
