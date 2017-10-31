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
