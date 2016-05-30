#ifndef AABB_H
#define AABB_H

#include "ColliderC.h"
#include "mat4.h"
#include "vec3.h"
#include <vector>
using namespace Math;

namespace pp
{
	class TransformationC;

	class AABB : public ColliderC
	{
	public:

		void update(const float& dt) override;
		void draw(void) const override; // debug purpose
		void save(ofstream& myFile, const unsigned int & guid) override;

		AABB(void);
		virtual ~AABB(void);

		// Retrieves the center of the AABB.
		vec3f getCenter(void) const;

		// Retrieves the diagonal vector (computed as mMax - mMin).
		// If the AABB is NULL, then a vector of all zeros is returned.
		vec3f getDiagonal(void) const;

		// Returns true if AABBs share a face overlap.
		// \xxx Untested -- This function is not represented in our unit tests.
		bool overlaps(const AABB& bb) const;

		// Type returned from call to intersect.
		enum INTERSECTION_TYPE { INSIDE, INTERSECT, OUTSIDE };
		// Returns one of the intersection types. If either of the aabbs are invalid,
		// then OUTSIDE is returned.
		INTERSECTION_TYPE intersect(const AABB& bb);

		// Set the AABB as NULL (not set).
		void setNull(void) { mMin = vec3f(1.0); mMax = vec3f(-1.0); }

		// Returns true if AABB is NULL (not set).
		bool isNull(void) const { return mMin.x > mMax.x || mMin.y > mMax.y || mMin.z > mMax.z; }

		// get and setter
		void setPos(const vec3f &pos) { this->updatedFlag = true; this->position = pos; };
		void setHalfSize(const vec3f &halfsize) { updatedFlag = true; this->halfSize = halfsize; };
		vec3f getMin(void) const { return mMin; }
		vec3f getMax(void) const { return mMax; }
		vec3f getRPos(void) const { return rpos; }

		bool pointVSAABB(const vec3f& point);

		// for drawing instance
		static std::vector<mat4f> modelMats;

		INTERSECTION_TYPE intersectInfo;

	private:

		TransformationC* transform;

		vec3f mMin;   //< Minimum point.
		vec3f mMax;   //< Maximum point.

		vec3f position, halfSize;
		vec3f rpos, rscale;
	};
}

#endif


