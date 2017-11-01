#include <iostream>

#include "sfwdraw.h"
#include "mathutils.h"
#include "vec2.h"

#include "Transform.h"
#include "Player.h"
#include"drawutils.h"

#include "Polygon.h"


#include <cmath>

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

	Polygon box = {
		{
			{200,100},
			{400,100},
			{400,400},
			{200,400}
		},
		{
			{0,0}
		},
		4,
		Transform(nullptr)
	};

	Polygon triangle = {
		{
			{ 250,250 },
			{ 600,100 },
			{ 600,400 }
		},
		{
			{0,0}
		},
		3,
		Transform(nullptr)
	};

	CreateAxes(box);
	CreateAxes(triangle);

	////// Gather / determine all of the axes.
	vec2 axes[7];
	int naxes = 0;
	for (int i = 0; i < box.numPoints; ++i)
		axes[naxes++] = normal(perpendicular(box.points[i] - box.points[(i + 1)% box.numPoints], false));
	for (int i = 0; i < triangle.numPoints; ++i)
		axes[naxes++] = normal(perpendicular(triangle.points[i] - triangle.points[(i + 1) % triangle.numPoints], false));

	float fPD = FLT_MAX;
	vec2  fCN;
	bool  res = true;

	// For Each Axis
	for(int i = 0; i < naxes; ++i)
	{
		AExtent Aex = EvalAxialExtents(axes[i], box.points, 4);
		AExtent Bex = EvalAxialExtents(axes[i], triangle.points, 3);

		float lPD = Aex.max - Bex.min;
		float rPD = Bex.max - Aex.min;

		float PD  = min(lPD, rPD);
		float H   = copysignf(1, rPD - lPD); 
		vec2  CN  = axes[i] * H;

		res = res && PD >= 0;

		if((res && PD < fPD)  ||
		  (!res && (PD < 0) && (PD > fPD || fPD >= 0)))
		{
			fPD = PD;
			fCN = CN;
		}

		printf("Aex: max %f min %f \n", Aex.max, Aex.min);
		printf("lPd: %f , rPd %f \n", lPD, rPD);
		printf("PD %f, H %f, CN %f , %f \n", PD, H, CN.x, CN.y);
		printf("fPD %f, fCN %f \n", fPD, fCN);
		std::cout << res << std::endl << std::endl;

	}

	//~fin



	////// Test 1D collision across each axis
		//// project points of each hull onto axis, finding the min/max extents
		//// find the overlap

	///// Of all axes:
		//// if any overlap is non-overlapping:
			//// the result is the smallest non-overlapping axis ( shortest distance)
		//// else if return the axis of least separation (axis w/smallest overlap)
	

	printNormals(box.points, 4);
	printNormals(triangle.points, 3);

	vec2 mousePos = { 0,0 };

	while (sfw::stepContext())
	{
		mousePos = vec2{ sfw::getMouseX(), sfw::getMouseY() };
		triangle.transform.angle += sfw::getDeltaTime() * 100;

		//mousePos = {130,12};

		box.points[0] = mousePos;
		box.points[1] = mousePos + vec2{ 200,0 };
		box.points[2] = mousePos + vec2{ 200,200 };
		box.points[3] = mousePos + vec2{ 0,200 };


		//DrawAxes(box);
		//DrawAxes(triangle);

		DrawPolygon(box * box.transform.GetGlobalTransform());
		DrawPolygon(triangle * triangle.transform.GetGlobalTransform());

		auto test = DoPolygonsCollide(triangle * triangle.transform.GetGlobalTransform(),
			box * box.transform.GetGlobalTransform());

		if (test.penetration > 0)
		{
			sfw::setBackgroundColor(BLUE);
		}
		else
		{
			sfw::setBackgroundColor(BLACK);
		}

		//if (box.doesCollide(triangle).penetration > 0)
		//{
		//	sfw::setBackgroundColor(BLUE);
		//}
		//else
		//{
		//	sfw::setBackgroundColor(BLACK);
		//}
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
	Transform myTransform(nullptr);
	myTransform.position = vec2{ 300,400 };
	myTransform.dimension = vec2{ 1,1 };
	myTransform.angle = 90;

	Transform myBaby(nullptr);
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