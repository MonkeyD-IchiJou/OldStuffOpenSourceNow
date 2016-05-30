#include "BulletC.h"
#include "Entity.h"
#include "TransformationC.h"

namespace pp
{
	static float deactivateTime = 5.f;

	BulletC::BulletC(void) : Component(BULLET), transform(nullptr), timer(0.f), speed(30.f), K(0.f), collide(false)
	{
		ShootingRay.Set(0, 0, 1.f);
		
	}

	BulletC::~BulletC(void)
	{
	}

	void BulletC::update(const float& dt)
	{
		if (transform == nullptr) transform = getOwner()->transformC;

		if (updatedFlag)
		{
			if (getOwner()->isTag("HEALBULLET"))
			{
				speed = 15.f;
			}
			transform->position = InitFirePos;
			updatedFlag = false;
		}

		if (getOwner()->isActive())
		{
			timer += dt;
			if (timer > deactivateTime )
			{
				getOwner()->setActive(false);
				timer = 0.f;
			}

			if (collide == true)
			{
				getOwner()->setActive(false);
				timer = 0.f;
				collide = false;
			}

			prevPos = InitFirePos;
			transform->Translate(ShootingRay * dt * speed);
			currentPos = transform->position;

			transform->LookAt(ShootingRay, 1);
		}
	}

	void BulletC::save(ofstream & myFile, const unsigned int & guid)
	{
	}

	void BulletC::setInitFirePos(const vec3f & i)
	{
		this->InitFirePos = i;
		updatedFlag = true;
	}

	vec3f BulletC::getInitFirePos(void)
	{
		return InitFirePos;
	}

	void BulletC::setShootingRay(const vec3f & r)
	{
		ShootingRay = r;
	}

	vec3f BulletC::getShootingRay(void)
	{
		return ShootingRay;
	}
}
