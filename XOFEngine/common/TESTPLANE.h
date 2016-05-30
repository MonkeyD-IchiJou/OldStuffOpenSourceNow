#ifndef TEST_H
#define TEST_H

#include "vec3.h"
using namespace Math;

class PLANE {
public:
	float equation[4];
	vec3f origin;
	vec3f normal;
	PLANE(const vec3f& origin, const vec3f& normal);
	PLANE(const vec3f& p1, const vec3f& p2, const vec3f& p3);
	bool isFrontFacingTo(const vec3f& direction) const;
	double signedDistanceTo(const vec3f& point) const;
};

#endif