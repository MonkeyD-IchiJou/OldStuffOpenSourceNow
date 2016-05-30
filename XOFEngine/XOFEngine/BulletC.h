#ifndef BULLETC_H
#define BULLETC_H

#include "Component.h"
#include "vec3.h"
using namespace Math;

namespace pp
{
	class TransformationC;

	class BulletC :
		public Component
	{
	public:
		BulletC(void);
		virtual ~BulletC(void);

		virtual void update(const float& dt) override;
		virtual void save(ofstream& myFile, const unsigned int & guid) override;

		void setInitFirePos(const vec3f& i);
		vec3f getInitFirePos(void);

		void setShootingRay(const vec3f& r);
		vec3f getShootingRay(void);

		vec3f currentPos;
		vec3f prevPos;
		vec3f intersectionPoint;
		float K;
		bool collide;

	private:
		vec3f ShootingRay;
		vec3f InitFirePos;
		float timer, speed;

		TransformationC* transform;
	};
}

#endif 

