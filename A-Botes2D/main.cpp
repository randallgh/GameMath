#include "Transform.h"

#include "sfwdraw.h"
#include "Screen.h"

//Ship
#include "Ship.h"
#include "Hull.h"
int main() 
{
	ScreenInfo SCR_INFO;
	sfw::initContext(SCR_INFO.SCR_WIDTH, SCR_INFO.SCR_HEIGHT, SCR_INFO.SCR_NAME);

	Hull * akizukiHull = new Hull[3];
	Ship Akizuki();

	while (sfw::stepContext())
	{
		float t = sfw::getDeltaTime();

	}

	sfw::termContext();
	return 0;
}