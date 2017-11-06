#pragma once
#include "vec2.h"
#include "mat3x3.h"

class Physics;
class GameObject;

static enum ColliderType
{
	Circle,
	SAT
};

struct SATGeometry
{
	vec2 points[16];
	int numPoints;
	vec2 axes[16];
};

SATGeometry operator*(const SATGeometry &P, const mat3x3 &M);
struct AxialExtents { float min, max; };

//Creates the Axes for the SATGeometry passed in
void CreateAxes(SATGeometry &poly);

struct Collision
{
	//Multiply all by each other and add to the position of the GameObject that
	//you do not want to collide with.
	float penetration;
	vec2 collisionNormal;
	//float handedness;
};

//Whenever a collider is constructed it must be added to the physics array
class Collider
{
public:
	Collider(GameObject * go, Physics * phys);
	Collider(const SATGeometry &G, GameObject * go, Physics * phys);
	~Collider();

	//void update();
	void draw(mat3x3 cam);
	Collision doesCollide(Collider * other);

	ColliderType type;
	SATGeometry geometry;

	GameObject * gameObject;

private:
	static Collision DoesCollide_SAT_SAT(const SATGeometry &A, const SATGeometry &B);

	static Collision DoesCollide_CIRCLE_CIRCLE(const Collider &A, const Collider &B);

	//Not yet implemented
	static Collision DoesCollide_SAT_CIRCLE();

	static AxialExtents EvalAxialExtents(const vec2 &axis, const vec2 *points, size_t size);
};