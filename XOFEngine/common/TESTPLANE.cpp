#include "TESTPLANE.h"

PLANE::PLANE(const vec3f& origin, const vec3f& normal) 
{
	this->normal = normal;
	this->origin = origin;
	equation[0] = normal.x;
	equation[1] = normal.y;
	equation[2] = normal.z;
	equation[3] = -(normal.x*origin.x + normal.y*origin.y
		+ normal.z*origin.z);
}

PLANE::PLANE(const vec3f& p1, const vec3f& p2,
	const vec3f& p3)
{
	normal = (p2 - p1).cross(p3 - p1);

	if (!normal.IsZero())
	{
		normal.normalize();
	}
	
	origin = p1;
	equation[0] = normal.x;
	equation[1] = normal.y;
	equation[2] = normal.z;
	equation[3] = -(normal.x*origin.x + normal.y*origin.y
		+ normal.z*origin.z);
}

bool PLANE::isFrontFacingTo(const vec3f& direction) const 
{
	double dot = normal.dot(direction);
	return (dot <= 0);
}
double PLANE::signedDistanceTo(const vec3f& point) const 
{
	return (point.dot(normal)) + equation[3];
}