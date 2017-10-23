#pragma once
#include <string>

class Collider;
class PlayerData;

class Physics
{
public:
	Physics();
	~Physics();
	void update();
	bool addCollider(Collider * collider);
	PlayerData * playerData;

private:
	static const int MAX_COLLIDERS = 500;
	Collider ** colliders;

	//Fucntion for tag collision
	int isCollide(int i, int o, std::string tag1, std::string tag2);
};