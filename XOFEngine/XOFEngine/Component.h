#ifndef COMPONENT_H
#define COMPONENT_H

#include <fstream>
using std::ofstream;
#include "enumc.h"

namespace pp
{
	class Entity;
	class ComponentsPool;

	class Component
	{
	public:

		// constructor and take in type
		Component(const COMPONENT_TYPE& l_type = NONE);

		// default virtual destructor for polymorphism
		virtual ~Component(void);

		// every components got its very own update methods
		virtual void update(const float &dt) = 0;

		// every components are able to save themself 
		virtual void save(ofstream& myFile, const unsigned int& guid) = 0;

		// set the owner
		void setOwner(Entity *l_owner);

		// get the owner entity
		Entity* getOwner(void) const;

		// the components pool where this component belong
		inline void setDaddy(ComponentsPool* d) { this->daddy = d; }

		// set type of this component
		inline void setType(const COMPONENT_TYPE& l_type) { this->m_type = l_type; }

		// get the type of the component
		inline COMPONENT_TYPE getType(void) const { return this->m_type; }

		// a flag for component to update itself or not .. 
		// e.g if updateFlag is true .. the component will update in this frame
		bool updatedFlag;

		// the place where it belong
		ComponentsPool* daddy;

	private:

		// hold the owner reference
		Entity* m_owner;

		// every componet got its own type
		COMPONENT_TYPE m_type;
	};
}

#endif

