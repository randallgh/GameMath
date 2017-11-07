#pragma once
class Transform;
class Collider;
class Rigidbody;

#include <string>

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform * transform;
	Collider * collider;
	Rigidbody * rigidbody;

	bool isEnabled;
	std::string tag;
	std::string name;
	unsigned int color;

	void update();

private:

};