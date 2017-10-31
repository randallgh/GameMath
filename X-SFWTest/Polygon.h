#pragma once
#include "vec2.h"
#include "Transform.h"
#include "drawutils.h"
#include "mat3x3.h"


struct Polygon
{
	vec2 points[16];
	vec2 axes[16];
	int numPoints;
	Transform transform;
};

void CreateAxes(Polygon &poly)
{
	for (int i = 0; i < poly.numPoints; ++i)
	{
		poly.axes[i] = normal(perpendicular(poly.points[i] - poly.points[(i + 1) % poly.numPoints], false));
	}
}

void DrawAxes(const Polygon &poly)
{
	for (int i = 0; i < poly.numPoints; i++)
	{
		drawVecLine(poly.axes[i], poly.axes[(i + 1) % poly.numPoints]);
		//sfw::drawLine(
		//	poly.axes[i].x,
		//	poly.axes[i].y,
		//	poly.axes[(i + 1) % poly.numPoints].x,
		//	poly.axes[(i + 1) % poly.numPoints].y,
		//	RED);
	}
}

Polygon operator*(const Polygon &P, const mat3x3 &M)
{
	Polygon retval;
	retval.numPoints = P.numPoints;
	retval.transform = P.transform;

	for (int i = 0; i < retval.numPoints; ++i)
	{
		vec2 point = (M * vec3{ P.points[i].x,P.points[i].y,1 }).xy;
		retval.points[i] = point;
	}
	CreateAxes(retval);

	return retval;
}

void DrawPolygon(const Polygon &poly)
{
	for (int i = 0; i < poly.numPoints; i++)
	{
		drawVecLine(poly.points[i], poly.points[(i + 1) % poly.numPoints], WHITE);
	}
}

struct AExtent { float min, max; };

AExtent EvalAxialExtents(const vec2 &axis, const vec2 *points, size_t size)
{
	AExtent res = { INFINITY, -INFINITY };

	for (int i = 0; i < size; ++i)
	{
		float proj = dot(axis, points[i]);

		res.min = min(proj, res.min);
		res.max = max(proj, res.max);
	}

	return res;
}

struct Coll
{
	float penetration;
	vec2 collisionNormal;
};

Coll DoPolygonsCollide(const Polygon &A, const Polygon &B)
{
	vec2 axes[32];

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

	float PD = 0;
	vec2 CN = { 0,0 };

	for (int i = 0; i < naxes; ++i)
	{
		AExtent Aex = EvalAxialExtents(axes[i], A.points, A.numPoints);
		AExtent Bex = EvalAxialExtents(axes[i], B.points, B.numPoints);

		float lPD = Aex.max - Bex.min;
		float rPD = Bex.max - Aex.min;

		PD = min(lPD, rPD);
		float H = copysignf(1, rPD - lPD);
		CN = axes[i] * H;

		res = res && PD >= 0;



		if ((res && PD < fPD) ||
			(!res && (PD < 0) && (PD > fPD || fPD >= 0)))
		{
			fPD = PD;
			fCN = CN;
		}

		if (!res)
		{
			return Coll{ PD, CN };
		}
	}

	return Coll{ PD, CN };
}
