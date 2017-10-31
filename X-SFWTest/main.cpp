#include <iostream>

#include "sfwdraw.h"
#include "mathutils.h"
#include "vec2.h"

#include "Transform.h"
#include "Player.h"
#include <cmath>


struct AxialExtents { float min, max; };

AxialExtents EvalAxialExtents(const vec2 &axis, const vec2 *points, size_t size)
{
	AxialExtents res = {FLT_MAX, FLT_MIN};

	for (int i = 0; i < size; ++i)
	{
		float proj = dot(axis, points[i]);

		res.min = min(proj, res.min);
		res.max = max(proj, res.max);
	}

	return res;
}


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
	

	////// Gather / determine all of the axes.
	vec2 axes[7];
	int naxes = 0;
	for (int i = 0; i < 4; ++i)
		axes[naxes++] = normal(perpendicular(boxPoints[i] - boxPoints[(i + 1)%4], false));
	for (int i = 0; i < 3; ++i)
		axes[naxes++] = normal(perpendicular(trianglePoints[i] - trianglePoints[(i + 1) % 3], false));

	float fPD = FLT_MAX;
	vec2  fCN;
	bool  res = true;

	// For Each Axis
	for(int i = 0; i < naxes; ++i)
	{
		AxialExtents Aex = EvalAxialExtents(axes[i], boxPoints, 4);
		AxialExtents Bex = EvalAxialExtents(axes[i], trianglePoints, 3);

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
	}

	//~fin



	////// Test 1D collision across each axis
		//// project points of each hull onto axis, finding the min/max extents
		//// find the overlap

	///// Of all axes:
		//// if any overlap is non-overlapping:
			//// the result is the smallest non-overlapping axis ( shortest distance)
		//// else if return the axis of least separation (axis w/smallest overlap)
	

	printNormals(boxPoints, 4);
	printNormals(trianglePoints, 3);

	vec2 normVec = normal(perpendicular(boxPoints[1] - boxPoints[2], false));
	printf("Dot: %f %f \n", normVec.x, normVec.y);
	vec2 v = projection(boxPoints[0] - boxPoints[1], normVec);
	printf("Dot: %f %f \n", v.x, v.y);
	v = projection(boxPoints[3] - boxPoints[2], normVec);
	printf("Dot: %f %f \n", v.x, v.y);

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