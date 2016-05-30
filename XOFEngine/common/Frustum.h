#ifndef FRUSTUM_H
#define FRUSTUM_H

#define FRUSTUM_NEAR  0
#define FRUSTUM_FAR   1
#define FRUSTUM_LEFT  2
#define FRUSTUM_RIGHT 3
#define FRUSTUM_UP    4
#define FRUSTUM_DOWN  5

#include "Plane.h"
#include "vec3.h"
#include "mat4.h"

namespace Math
{
	// Frustum class defined by six planes enclosing the frustum. The normals face inward.
	class CFrustum
	{
	public:
		CFrustum(void);
		void setVP(const mat4f& mm);
		~CFrustum(void);

	public:
		bool SphereIntersection(const vec3f& vecCenter, const float& flRadius);

	public:
		CPlane p[6];
	};
}

#endif