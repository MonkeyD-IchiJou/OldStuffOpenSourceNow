#include "ColliderC.h"

namespace pp
{
	ColliderC::ColliderC(COLLIDER_TYPE type) : Component(RENDERER), type(type), collide(false), guid(0)
	{
		setTag("default");
	}
	ColliderC::~ColliderC(void)
	{
	}
	void ColliderC::update(const float& dt)
	{
	}
	void ColliderC::save(ofstream & myFile, const unsigned int & guid)
	{
	}
}
