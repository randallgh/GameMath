#include <iostream>

#include "sfwdraw.h"
#include "mathutils.h"
#include "vec2.h"

#include "Player.h"

int main() 
{
	sfw::initContext();
	sfw::setBackgroundColor(BLACK);

	vec2 test = { 0,0 };
	Player player;
	player.position = { 200,200 };
	player.velocity = { 1,1 };

	while (sfw::stepContext())
	{
		player.update();
		player.draw();
	}

	return 0;
}