#include "Component.h"

namespace pp
{

	Component::Component(const COMPONENT_TYPE& l_type) : 
		m_owner(nullptr),
		daddy(nullptr),
		m_type(NONE),
		updatedFlag(true)
	{
	}

	Component::~Component(void)
	{
	}

	// set the owner
	void Component::setOwner(Entity *l_owner)
	{
		this->m_owner = l_owner;
	}

	// get the owner entity
	Entity* Component::getOwner(void) const
	{
		return this->m_owner;
	}

}
