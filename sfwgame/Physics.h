#pragma once
#include <string>

class Collider;
class Camera;

class Physics
{
public:
	Physics(Camera * c);
	~Physics();
	void update();
	bool addCollider(Collider * collider);

private:
	static const int MAX_COLLIDERS = 500;
	Collider ** colliders;
	Camera * cam;

	//Fucntion for tag collision
	int isCollide(int i, int o, std::string tag1, std::string tag2);
	int isCollide(int i, int o, std::string tag);
};
