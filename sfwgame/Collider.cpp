#include "Collider.h"
#include "Transform.h"
#include "sfwdraw.h"
#include "drawutils.h"
#include "Physics.h"
#include "GameObject.h"
#include "mathutils.h"
#include "Rigidbody.h"

Collider::Collider(GameObject * go, Physics * phys)
{
	type = ColliderType::Circle;

	gameObject = go;

	if (phys != nullptr) { phys->addCollider(this); };
}

Collider::Collider(SATGeometry G, GameObject * go, Physics * phys)
{
	type = ColliderType::SAT;
	gameObject = go;

	if (phys != nullptr) { phys->addCollider(this); };

	geometry.numPoints = G.numPoints;
	for (int i = 0; i < geometry.numPoints; ++i)
	{
		geometry.points[i] = G.points[i];
	}
	CreateAxes(geometry);
}

Collider::~Collider()
{

}

//Does collide with other SATGeometry
Collision Collider::DoesCollide_SAT_SAT(const SATGeometry &A, const SATGeometry &B)
{
	vec2 axes[SATGeometry::MAX_POINTS * 2];

	int naxes = 0;
	for (int i = 0; i < A.numPoints; ++i)
	{
		axes[naxes++] = A.axes[i];
	}
	for (int i = 0; i < B.numPoints; ++i)
	{
		axes[naxes++] = B.axes[i];
	}

	float fPD = FLT_MAX;
	vec2  fCN;
	bool  res = true;

	for (int i = 0; i < naxes; ++i)
	{
		AxialExtents Aex = EvalAxialExtents(axes[i], A.points, A.numPoints);
		AxialExtents Bex = EvalAxialExtents(axes[i], B.points, B.numPoints);

		float lPD = Aex.max - Bex.min;
		float rPD = Bex.max - Aex.min;

		float PD = min(lPD, rPD);
		float H = copysignf(1, lPD - rPD);
		vec2 CN = axes[i] * H;

		res = res && PD >= 0;



		if ((res && PD < fPD) ||
			(!res && (PD < 0) && (PD > fPD || fPD >= 0)))
		{
			fPD = PD;
			fCN = CN;
		}

		if (!res)
		{
			return Collision{ fPD, fCN};
		}
	}

	return Collision{ fPD, fCN};
}

Collision Collider::DoesCollide_CIRCLE_CIRCLE(const Collider & A, const Collider & B)
{
	vec2 aPos = A.gameObject->transform->GetGlobalTransform().c[2].xy;
	vec2 bPos = B.gameObject->transform->GetGlobalTransform().c[2].xy;

	float dist = distance(aPos, bPos);

	float aR = A.gameObject->rigidbody->radius;
	float bR = B.gameObject->rigidbody->radius;

	if (dist < aR + bR)
	{
		return Collision{ (aR + bR) - dist, normal(bPos - aPos) };
	}

	return Collision{ 0, {0,0} };
}

Collision Collider::doesCollide(Collider * other)
{
	if (other->type == ColliderType::SAT 
		&& this->type == ColliderType::SAT)
	{
		return DoesCollide_SAT_SAT(geometry 
			* gameObject->transform->GetGlobalTransform() , 
			other->geometry 
			* other->gameObject->transform->GetGlobalTransform());
	}
	else if (other->type == ColliderType::Circle 
		&& this->type == ColliderType::Circle)
	{
		return DoesCollide_CIRCLE_CIRCLE(*this, *other);
	}

	return Collision{ 0, {0,0} };
}

AxialExtents Collider::EvalAxialExtents(const vec2 & axis, const vec2 * points, 
										size_t size)
{
	AxialExtents res = { INFINITY, -INFINITY };

	for (int i = 0; i < size; ++i)
	{
		float proj = dot(axis, points[i]);

		res.min = min(proj, res.min);
		res.max = max(proj, res.max);
	}

	return res;
}

//void Collider::update()
//{
//	if (this == nullptr) { return; }
//	if (!gameObject->isEnabled) { return; }
//	
//}
//

void Collider::draw(mat3x3 cam)
{
	if (this == nullptr) { return; }

	if (!gameObject->isEnabled) { return; }

	switch (type)
	{
	case Circle:
		drawVecCircle((cam * gameObject->transform->GetGlobalTransform()).c[2].xy, gameObject->rigidbody->radius, 12, WHITE);
		break;
	case SAT:
		SATGeometry geo = (geometry * cam );
		for (int i = 0; i < geo.numPoints; i++)
		{
			if (gameObject->color == 0) 
			{ 
				gameObject->color = WHITE; 
			}
			drawVecLine(geo.points[i], geo.points[(i + 1) % geo.numPoints], gameObject->color);
		}
		break;
	default:
		break;
	}
	
}

SATGeometry operator*(const SATGeometry & P, const mat3x3 & M)
{
	SATGeometry retval;
	retval.numPoints = P.numPoints;

	for (int i = 0; i < retval.numPoints; ++i)
	{
		vec2 point = (M * vec3{ P.points[i].x,P.points[i].y,1 }).xy;
		retval.points[i] = point;
	}
	CreateAxes(retval);

	return retval;
}

void CreateAxes(SATGeometry & poly)
{
	for (int i = 0; i < poly.numPoints; ++i)
	{
		poly.axes[i] = normal(perpendicular(poly.points[i] - poly.points[(i + 1) % poly.numPoints], false));
	}
}
