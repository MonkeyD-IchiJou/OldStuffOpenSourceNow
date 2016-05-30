#include "SphereColliderC.h"
#include "Entity.h"
#include "TransformationC.h"


namespace pp
{
	std::vector<mat4f> SphereColliderC::modelMats;
	CFrustum* SphereColliderC::frustumHandle = nullptr;

	SphereColliderC::SphereColliderC() : 
		ColliderC(SPHERE_TYPE), 
		fradius(1.f), 
		localpos(nullptr)
	{
	}

	SphereColliderC::~SphereColliderC(void)
	{
		localpos = nullptr;
	}

	void SphereColliderC::update(const float& dt)
	{
		if (updatedFlag)
		{
			if (localpos == nullptr) localpos = &getOwner()->transformC->localPosition;

			updatedFlag = false;
		}
	}

	void SphereColliderC::draw(void) const
	{
		if (getOwner()->isActive())
		{
			if (localpos)
			{
				mat4f t, s;
				t.SetToTranslation(localpos->x, localpos->y, localpos->z);
				s.SetToScale(fradius, fradius, fradius);
				modelMats.push_back(t * s);
			}
		}
	}

	void SphereColliderC::setfradius(const float & radius)
	{
		this->fradius = radius;
	}

	float SphereColliderC::getfradius(void) const
	{
		return fradius;
	}

	bool SphereColliderC::frustumCull(const std::string& tag) 
	{
		if (frustumHandle)
		{
			if ( isTag(tag) && !frustumHandle->SphereIntersection(*localpos, fradius))
			{
				// if it is not inside the frustum, return false
				return false;
			}
		}

		return true;
	}

	void SphereColliderC::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.addSphereCollider(" << guid << ") \n";

		myFile << "Entity.getSphereCollider.setRadius(" << guid << ", " << fradius << ") \n";
	}
}
