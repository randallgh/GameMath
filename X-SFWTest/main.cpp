#include <iostream>

#include "sfwdraw.h"
#include "mathutils.h"
#include "vec2.h"

#include "Transform.h"
#include "Player.h"


void printNormals(const vec2 * points, int count)
{
	vec2 normVec;
	for (int i = 0; i < count; ++i)
	{
		if ((i + 1) == count)
		{
			normVec = normal(perpendicular(points[i] - points[0], false));
		} 
		else 
		{
			normVec = normal(perpendicular(points[i] - points[i + 1], false));
		}
		printf("Normal X: %f Y: %f \n", normVec.x, normVec.y);
	}
}

int main() 
{
	sfw::initContext(800,600,"SFW MathLib Test");
	sfw::setBackgroundColor(BLACK);

	vec2 boxPoints[4] = {
		{2,1},
		{4,1},
		{ 4,4 },
		{2,4}
		 };

	vec2 trianglePoints[3] = {
		{ 6,2.5 },
		{ 8,1 },
		{ 8,4 } };

	printNormals(boxPoints, 4);
	printNormals(trianglePoints, 3);

	vec2 normVec = normal(perpendicular(boxPoints[0] - boxPoints[1], false));

	float v = dot(normVec, boxPoints[0] - boxPoints[1]);
	printf("Dot: %f \n", v);
	v = dot(normVec, boxPoints[3] - boxPoints[2]);
	printf("Dot: %f \n", v);

	//vec2 normVec = normal(perpendicular(boxPoints[0] - boxPoints[1], false));
	//printf("Normal X: %f Y: %f \n", normVec.x,normVec.y);

	//normVec = normal(perpendicular(boxPoints[1] - boxPoints[2], false));
	//printf("Normal X: %f Y: %f \n", normVec.x, normVec.y);

	//normVec = normal(perpendicular(boxPoints[2] - boxPoints[3], false));
	//printf("Normal X: %f Y: %f \n", normVec.x, normVec.y);

	//normVec = normal(perpendicular(boxPoints[3] - boxPoints[0], false));
	//printf("Normal X: %f Y: %f \n", normVec.x, normVec.y);


	while (sfw::stepContext())
	{

	}

	sfw::termContext();
	return 0;
}

void playerThing()
{
	Player player;
	player.position = { 400,300 };
	player.velocity = { 0,0 };

	player.mass = 1;
	player.acceleration = { 0,0 };


	float speed = 20;
	vec2 w = { 0,speed };
	vec2 a = { -speed,0 };
	vec2 s = { 0,-speed };
	vec2 d = { speed, 0 };

	vec2 min = { 0,0 };
	vec2 max = { 800,600 };

	vec2 maxAcceleration = { 100,100 };
	vec2 maxVelocity = { 100,100 };

	vec2 dragA = { 0.4,0.4 };
	vec2 dragV = { 0.2,0.2 };
	
		//clamp(player.position, min, max);
		clamp(player.acceleration, -maxAcceleration, maxAcceleration);
		clamp(player.velocity, -maxVelocity, maxVelocity);

		player.update();
		//float viewMatrix[16] = {1,0,0,0, 
		//						0,1,0,0,
		//						0,0,1,0, 
		//						0,0,0,1};

		////sfw::setProjectionMatrix(sfw::identity);

		//sfw::setViewMatrix(viewMatrix);

		player.draw();

		if (player.acceleration.x > 0)
		{
			player.acceleration.x -= dragA.x;
		}
		else if (player.acceleration.x < 0)
		{
			player.acceleration.x += dragA.x;
		}
		if (player.acceleration.y > 0)
		{
			player.acceleration.y -= dragA.y;
		}
		else if (player.acceleration.y < 0)
		{
			player.acceleration.y += dragA.y;
		}

		if (player.velocity.x > 0)
		{
			player.velocity.x -= dragV.x;
		}
		else if (player.velocity.x < 0)
		{
			player.velocity.x += dragV.x;
		}
		if (player.velocity.y > 0)
		{
			player.velocity.y -= dragV.y;
		}
		else if (player.velocity.y < 0)
		{
			player.velocity.y += dragV.y;
		}



		if (sfw::getKey(87))
		{
			std::cout << "Boop" << std::endl;
			player.acceleration += w;
		}
		if (sfw::getKey(65))
		{
			player.acceleration += a;
		}
		if (sfw::getKey(83))
		{
			player.acceleration += s;
		}
		if (sfw::getKey(68))
		{
			player.acceleration += d;
		}
}

void transformThings()
{
	Transform myTransform;
	myTransform.position = vec2{ 300,400 };
	myTransform.dimension = vec2{ 1,1 };
	myTransform.angle = 90;

	Transform myBaby;
	myBaby.position = vec2{ 30,30 };
	myBaby.dimension = vec2{ 1,1 };
	myBaby.e_parent = &myTransform;
	myBaby.angle = 0;

	//Game Loop

	float t = sfw::getDeltaTime();
	myTransform.angle += sfw::getDeltaTime() * 100;
	myBaby.angle += sfw::getDeltaTime() * -100;

	/*myTransform.dimension = vec2{ sinf(t/2 + 1), sinf(t/2 + 1) + 2 };
	myBaby.position = vec2{ 0, sinf(t)*1000};*/

	DrawMatrix(myTransform.GetGlobalTransform(), 40);
	DrawMatrix(myBaby.GetGlobalTransform(), 30);
}