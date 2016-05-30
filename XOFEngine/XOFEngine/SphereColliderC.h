#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "ColliderC.h"

#include <vector>

#include "mat4.h"

#include "Frustum.h"

using namespace Math;

namespace pp
{
	class SphereColliderC : public ColliderC
	{
	public:
		SphereColliderC(void);
		virtual ~SphereColliderC(void);

		void update(const float& dt) override;
		void draw(void) const override;
		void save(ofstream& myFile, const unsigned int & guid) override;

		void setfradius(const float &radius);
		float getfradius(void) const;

		bool frustumCull(const std::string& tag);

		static std::vector<mat4f> modelMats;
		static CFrustum* frustumHandle;

	private:
		float fradius;
		vec3f *localpos;
		
	};
}

#endif

