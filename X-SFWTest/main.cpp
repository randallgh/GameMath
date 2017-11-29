#include <iostream>

#include "sfwdraw.h"
#include "mathutils.h"
#include "vec2.h"

#include "Transform.h"
#include "Player.h"
#include"drawutils.h"

#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Spritesheet.h"

#include "Polygon.h"
#include <random>
#include <chrono>
#include <cmath>

#include "Input.h"

#include "noise\noise.h"
#include "noiseutils.h"

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

size_t screen_width = 1280;
size_t screen_height = 720;

struct rgba
{
	unsigned r;
	unsigned g;
	unsigned b;
	unsigned a;

	unsigned hex()
	{
		return r << 24 | g << 16 | b << 8 | a << 0;
	}

	void set(unsigned hex)
	{
		r = (hex >> 24) & 0xFF;
		g = (hex >> 16) & 0xFF;
		b = (hex >>  8) & 0xFF;
		a = hex & 0xFF;
	}
};

int main() 
{
	sfw::initContext(screen_width, screen_height, "SFW MathLib Test");
	sfw::setBackgroundColor(BLACK);

	Input * input = new Input();


	std::default_random_engine gen(time(NULL));
	std::uniform_real_distribution<float> urd(0, 1);

	Spritesheet * tileset = new Spritesheet("Bisasam_16x16.png", 16, 16);

	const int horzSprites = screen_width / tileset->GetSpriteWidth();
	const int vertSprites = screen_height / tileset->GetSpriteHeight();

	vec2 * spriteLocations = new vec2[horzSprites * vertSprites];
	float * heightmap = new float[horzSprites * vertSprites];

	noise::module::Perlin perlin;


	int octave = 6;
	float freq = 50;
	perlin.SetFrequency(freq);
	perlin.SetOctaveCount(octave);

	float lowerXBound = 0;
	float upperXBound = 0.1;
	
	float lowerYBound = 0;
	float upperYBound = 0.1;


	utils::NoiseMap map;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(perlin);
	heightMapBuilder.SetDestNoiseMap(map);
	heightMapBuilder.SetDestSize(horzSprites, vertSprites);
	heightMapBuilder.SetBounds(lowerXBound, upperXBound, lowerYBound, upperYBound);
	heightMapBuilder.Build();

	//utils::RendererImage renderer;
	//utils::Image image;
	//renderer.SetSourceNoiseMap(map);
	//renderer.SetDestImage(image);
	//renderer.Render();

	//utils::WriterBMP writer;
	//writer.SetSourceImage(image);
	//writer.SetDestFilename("tutorial.bmp");
	//writer.WriteDestFile();


	rgba color = { 255,255,255,255 };
	//color.set(WHITE);

	float panSpeed = 0.01;
	int drawSprite = 11 * 16 + 1;

	while (sfw::stepContext())
	{
		input->poll();

		//Increase detail
		if (input->getKeyDown(KEY_L))
		{
			octave++;
			octave = clamp(octave, 10, 1);
		}
		//Decrease detail
		else if (input->getKeyDown(KEY_K))
		{
			octave--;
			octave = clamp(octave, 10, 1);
		}

		//Zoom out
		if (sfw::getKey(KEY_N))
		{
			freq += 1;
		}
		//Zoom in
		else if (sfw::getKey(KEY_M))
		{
			freq -= 1;
		}

		if (sfw::getKey(KEY_I))
		{
			perlin.SetPersistence(0.25f);
		}
		if (sfw::getKey(KEY_O))
		{
			perlin.SetPersistence(0.50f);
		}
		if (sfw::getKey(KEY_P))
		{
			perlin.SetPersistence(0.75f);
		}


		if (sfw::getKey(KEY_W))
		{
			lowerYBound += panSpeed;
			upperYBound += panSpeed;
		}
		else if (sfw::getKey(KEY_A))
		{
			lowerXBound -= panSpeed;
			upperXBound -= panSpeed;
		}
		else if (sfw::getKey(KEY_S))
		{
			lowerYBound -= panSpeed;
			upperYBound -= panSpeed;
		}
		else if (sfw::getKey(KEY_D))
		{
			lowerXBound += panSpeed;
			upperXBound += panSpeed;
		}

		perlin.SetOctaveCount(octave);
		perlin.SetFrequency(freq);
		heightMapBuilder.SetBounds(lowerXBound, upperXBound, lowerYBound, upperYBound);
		heightMapBuilder.Build();

		for (int y = 0; y < vertSprites; ++y)
		{
			for (int x = 0; x < horzSprites; ++x)
			{
				spriteLocations[x + y * horzSprites]
					= vec2{ tileset->GetSpriteWidth() * (float)x, tileset->GetSpriteHeight() * (float)y };
				heightmap[x + y * horzSprites] = clamp( ((map.GetValue(x, y) + 1) / 2), 1.0f , 0.2f);

			}
		}
		for (int i = 0; i < horzSprites * vertSprites; ++i)
		{
			if (heightmap[i] >= 0.6f)
			{
				color.set(WHITE);
				color.a = 255 * clamp(heightmap[i], 1.0f, 0.4f);
				drawSprite = 1 * 16 + 14;
			}
			else if (heightmap[i] >= 0.4f)
			{
				color.set(GREEN);
				color.a = 255 * clamp(heightmap[i], 1.0f, 0.4f);
				drawSprite = 9 * 16 + 15;
			}
			else if (heightmap[i] >= 0.3)
			{
				color.set(YELLOW);
				color.a = 255 * clamp(heightmap[i], 1.0f, 0.7f);
				drawSprite = 15 * 16 + 7;
			}
			else if (heightmap[i] >= 0)
			{
				color.set(BLUE);
				color.a = 255 * clamp(heightmap[i], 1.0f, 0.4f);
				drawSprite = 15 * 16 + 7;
			}

			

			tileset->draw(spriteLocations[i], drawSprite,
				1, color.hex(), 0, Spritesheet::BOTTOM_LEFT);

		}
	}
		

	sfw::termContext();
	return 0;
}

void transformTesting()
{

	Sprite testSprite("test.png");
	Spritesheet * testSheet = new Spritesheet("exp2_0.png", 4, 4);
	Spritesheet * testSheetRedCell = new Spritesheet("canvas.png", 6, 10);
	Spritesheet * explosion = new Spritesheet("explosion.png", 9, 9);

	SpriteAnimation testAnimation(explosion, 1.0f);
	SpriteAnimation testRedAnimation(testSheetRedCell, 2.0f);

	unsigned testTex = sfw::loadTextureMap("test.png");
	Transform testTrans(nullptr);
	testTrans.position = vec2{ 400,300 };
	//testTrans.dimension = vec2{ (float)sfw::getTextureWidth(testTex), (float)sfw::getTextureHeight(testTex)};

	Polygon box = {
		{
			{ 200,100 },
			{ 400,100 },
			{ 400,400 },
			{ 200,400 }
		},
		{
			{ 0,0 }
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
			{ 0,0 }
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
		axes[naxes++] = normal(perpendicular(box.points[i] - box.points[(i + 1) % box.numPoints], false));
	for (int i = 0; i < triangle.numPoints; ++i)
		axes[naxes++] = normal(perpendicular(triangle.points[i] - triangle.points[(i + 1) % triangle.numPoints], false));

	float fPD = FLT_MAX;
	vec2  fCN;
	bool  res = true;

	// For Each Axis
	for (int i = 0; i < naxes; ++i)
	{
		AExtent Aex = EvalAxialExtents(axes[i], box.points, 4);
		AExtent Bex = EvalAxialExtents(axes[i], triangle.points, 3);

		float lPD = Aex.max - Bex.min;
		float rPD = Bex.max - Aex.min;

		float PD = min(lPD, rPD);
		float H = copysignf(1, rPD - lPD);
		vec2  CN = axes[i] * H;

		res = res && PD >= 0;

		if ((res && PD < fPD) ||
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
		//sfw::drawTextureMatrix3(testTex, 0, WHITE,testTrans.GetGlobalTransform().m);
		box.points[0] = mousePos;
		box.points[1] = mousePos + vec2{ 200,0 };
		box.points[2] = mousePos + vec2{ 200,200 };
		box.points[3] = mousePos + vec2{ 0,200 };

		//testSheet->draw(testTrans.GetGlobalTransform(), (int)(sfw::getTime() * 20) % 16,2.0f,WHITE,0);
		testSprite.draw(translate(vec2{ 300,300 }) * testTrans.GetGlobalTransform(), tan(sfw::getTime()) * sfw::getTime(), RED, 1);

		testAnimation.update(sfw::getDeltaTime());
		testAnimation.draw(testTrans.GetGlobalTransform(), 4, WHITE, 0);

		testRedAnimation.update(sfw::getDeltaTime());
		testRedAnimation.draw(testTrans.GetGlobalTransform(), 1, WHITE, 0);

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