#include "Frustum.h"
#include "utils.h"

namespace Math
{
	CFrustum::CFrustum(void)
	{
		ZERO_MEM(p);
	}

	void CFrustum::setVP(const mat4f & mm)
	{
		mat4f m = mm.GetTranspose();//Transpose();

		p[FRUSTUM_RIGHT].n.x = m.a[12] - m.a[0];
		p[FRUSTUM_RIGHT].n.y = m.a[13] - m.a[1];
		p[FRUSTUM_RIGHT].n.z = m.a[14] - m.a[2];
		p[FRUSTUM_RIGHT].d = m.a[15] - m.a[3];

		p[FRUSTUM_LEFT].n.x = m.a[12] + m.a[0];
		p[FRUSTUM_LEFT].n.y = m.a[13] + m.a[1];
		p[FRUSTUM_LEFT].n.z = m.a[14] + m.a[2];
		p[FRUSTUM_LEFT].d = m.a[15] + m.a[3];

		p[FRUSTUM_DOWN].n.x = m.a[12] + m.a[4];
		p[FRUSTUM_DOWN].n.y = m.a[13] + m.a[5];
		p[FRUSTUM_DOWN].n.z = m.a[14] + m.a[6];
		p[FRUSTUM_DOWN].d = m.a[15] + m.a[7];

		p[FRUSTUM_UP].n.x = m.a[12] - m.a[4];
		p[FRUSTUM_UP].n.y = m.a[13] - m.a[5];
		p[FRUSTUM_UP].n.z = m.a[14] - m.a[6];
		p[FRUSTUM_UP].d = m.a[15] - m.a[7];

		p[FRUSTUM_FAR].n.x = m.a[12] - m.a[8];
		p[FRUSTUM_FAR].n.y = m.a[13] - m.a[9];
		p[FRUSTUM_FAR].n.z = m.a[14] - m.a[10];
		p[FRUSTUM_FAR].d = m.a[15] - m.a[11];

		p[FRUSTUM_NEAR].n.x = m.a[12] + m.a[8];
		p[FRUSTUM_NEAR].n.y = m.a[13] + m.a[9];
		p[FRUSTUM_NEAR].n.z = m.a[14] + m.a[10];
		p[FRUSTUM_NEAR].d = m.a[15] + m.a[11];

		// Normalize all plane normals
		for (int i = 0; i < 6; i++)
		{
			p[i].Normalize();
		}
	}

	CFrustum::~CFrustum(void)
	{
	}

	bool CFrustum::SphereIntersection(const vec3f & vecCenter, const float& flRadius)
	{
		// Loop through each plane that comprises the frustum.
		for (int i = 0; i < 6; i++)
		{
			// Plane-sphere intersection test. If p*n + d + r < 0 then we're outside the plane.
			if (vecCenter.dot(p[i].n) + p[i].d + flRadius <= 0)
			{
				return false;
			}
		}

		// If none of the planes had the entity lying on its "negative" side then it must be
		// on the "positive" side for all of them. Thus the entity is inside or touching the frustum.
		return true;
	}
}