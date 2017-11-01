#pragma once
#include <string>

class Collider;
struct Collision;
class Camera;
union vec2;

class Physics
{
public:
	Physics(Camera * c);
	~Physics();
	void update(float dt);
	bool addCollider(Collider * collider);

	static void static_resolution(vec2 & pos, vec2 & vel, const Collision & hit, float elasticity);

private:
	static const int MAX_COLLIDERS = 500;
	Collider ** colliders;
	Camera * cam;

	//Fucntion for tag collision
	int isCollide(int i, int o, std::string tag1, std::string tag2);
	int isCollide(int i, int o, std::string tag);
};
