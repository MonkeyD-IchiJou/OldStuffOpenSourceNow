#include "AABB.h"
#include "MyMath.h"
#include "Entity.h"
#include "TransformationC.h"

#include "ComponentsPool.h"

namespace pp
{
	std::vector<mat4f> AABB::modelMats;

	AABB::AABB(void) : 
		ColliderC(AABB_TYPE), 
		transform(nullptr),
		intersectInfo(OUTSIDE)
	{
		setNull();
	}

	void AABB::update(const float & dt)
	{
		// every frame update
		if (getOwner()->isActive())
		{
			if (transform == nullptr) transform = getOwner()->transformC;

			rpos = position + transform->localPosition;

			if (!isTag("GUI"))
				rscale = (halfSize * 2) + transform->scale;
			else
				rscale = (halfSize * 2);

			mMax = rpos + (rscale * 0.5f);
			mMin = rpos - (rscale * 0.5f);
		}
	}

	void AABB::draw(void) const
	{
		if (getOwner()->isActive())
		{
			mat4f t, s;
			t.SetToTranslation(rpos.x, rpos.y, rpos.z);
			s.SetToScale(rscale.x, rscale.y, rscale.z);
			modelMats.push_back(t * s);
		}
	}

	vec3f AABB::getDiagonal(void) const
	{
		if (!isNull())
			return mMax - mMin;
		else
			return vec3f(0);
	}

	vec3f AABB::getCenter(void) const
	{
		if (!isNull())
		{
			vec3f d = getDiagonal();
			return mMin + (d * float(0.5));
		}
		else
		{
			return vec3f(0.0);
		}
	}

	bool AABB::overlaps(const AABB& bb) const
	{
		if (getOwner()->isActive())
		{
			if (isNull() || bb.isNull())
				return false;

			if (bb.mMin.x > mMax.x || bb.mMax.x < mMin.x)
				return false;
			else if (bb.mMin.y > mMax.y || bb.mMax.y < mMin.y)
				return false;
			else if (bb.mMin.z > mMax.z || bb.mMax.z < mMin.z)
				return false;

			return true;
		}
		return false;
	}

	AABB::INTERSECTION_TYPE AABB::intersect(const AABB& b)
	{
		if (getOwner()->isActive())
		{
			if (isNull() || b.isNull())
			{
				collide = false;
				intersectInfo = OUTSIDE;
				return OUTSIDE;
			}
			

			if ((mMax.x < b.mMin.x) || (mMin.x > b.mMax.x) ||
				(mMax.y < b.mMin.y) || (mMin.y > b.mMax.y) ||
				(mMax.z < b.mMin.z) || (mMin.z > b.mMax.z))
			{
				collide = false;
				intersectInfo = OUTSIDE;
				return OUTSIDE;
			}

			if ((mMin.x <= b.mMin.x) && (mMax.x >= b.mMax.x) &&
				(mMin.y <= b.mMin.y) && (mMax.y >= b.mMax.y) &&
				(mMin.z <= b.mMin.z) && (mMax.z >= b.mMax.z))
			{
				collide = true;
				intersectInfo = INSIDE;
				return INSIDE;
			}

			collide = true;
			intersectInfo = INTERSECT;
			return INTERSECT;
		}

		collide = false;
		intersectInfo = OUTSIDE;
		return OUTSIDE;
	}

	bool AABB::pointVSAABB(const vec3f & point)
	{
		//Check if the point is less than max and greater than min
		if (point.x > mMin.x && point.x < mMax.x &&
			point.y > mMin.y && point.y < mMax.y &&
			point.z > mMin.z && point.z < mMax.z)
		{
			collide = true;
			return true;
		}

		//If not, then return false
		collide = false;
		return false;
	}



	AABB::~AABB(void)
	{
	}

	void AABB::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.addAABBCollider(" << guid << ") \n";

		myFile << "Entity.getAABBCollider.setHalfSize(" << guid << ", " << halfSize << ") \n";
		myFile << "Entity.getAABBCollider.setPosition(" << guid << ", " << position << ") \n";
	}
}
