#include "Entity.h"
#include "Component.h"
#include "TransformationC.h"

namespace pp
{
	Entity::Entity(void) : 
		transformC(nullptr), 
		active(false), 
		parent(nullptr), 
		scenetag("end"), 
		guid(0), 
		entityName("default name"), 
		bigDaddy(nullptr)
	{
		// note guid shld be unique
	}

	Entity::~Entity(void)
	{
	}

	void Entity::update(const float & dt)
	{
		if (active)
		{
			for (auto &x : containerC)
			{
				x->update(dt);
			}
		}
	}

	void Entity::AddComponent(Component * l_component)
	{
		// this component is belonged to this entity
		l_component->setOwner(this);
		containerC.push_back(l_component);
	}

	Component * Entity::findComponent(COMPONENT_TYPE t)
	{
		for (auto &x : containerC)
		{
			if (x->getType() == t)
			{
				return x;
			}
		}

		return nullptr;
	}

	unsigned int Entity::getGUID(void)
	{
		return this->guid;
	}

	void Entity::setGUID(const unsigned int & id)
	{
		this->guid = id;
	}

	void Entity::componentsUpdateFlagUpdate(void)
	{
		if (!active)
		{
			for (auto &x : containerC)
			{
				x->updatedFlag = false;
			}
		}

		if (active)
		{
			for (auto &x : containerC)
			{
				x->updatedFlag = true;
			}
		}
	}

	void Entity::setActive(const bool & active)
	{
		this->active = active;
		componentsUpdateFlagUpdate();
	}

	bool Entity::isActive(void)
	{
		return this->active;
	}

	void Entity::setParent(Entity * parent)
	{
		this->parent = parent;
	}

	Entity * Entity::getParent(void)
	{
		return this->parent;
	}

	void Entity::setChild(Entity * child)
	{
		children.push_back(child);
	}

	void Entity::resetUpdateFlag(COMPONENT_TYPE t)
	{
		for (auto &x : containerC)
		{
			if (x->getType() == t)
			{
				x->updatedFlag = true;
			}
		}
	}

	void Entity::setSceneTag(const string & tag)
	{
		this->scenetag = tag;
	}

	string Entity::getSceneTag(void) const
	{
		return scenetag;
	}

	void Entity::setTag(const string & n)
	{
		this->tags.push_back(n);
	}

	bool Entity::isTag(const string & tag)
	{
		for (auto &x : tags)
		{
			if (x == tag)
			{
				return true;
			}
		}

		return false;
	}

	std::vector<string>& Entity::getTag(void)
	{
		return tags;
	}

	void Entity::destroy(void)
	{
		// component manager will delete it all
		containerC.clear();

		if (children.size() > 0)
			children.clear();

		parent = nullptr;
	}

	void Entity::pureDestroy(void)
	{
		containerC.clear();

		if(children.size() > 0)
			children.clear();

		parent = nullptr;
	}

	int Entity::getTotalComponentSize(void)
	{
		return containerC.size();
	}

	void Entity::save(ofstream & myFile)
	{
		if (parent)
		{
			myFile << "Entity.addParent(" << getGUID() << " , " << parent->getGUID() << ") \n";
		}

		myFile << "Entity.setActive(" << getGUID() << " , " << btos(active) << ") \n";

		for (auto&x : tags)
		{
			myFile << "Entity.setTag(" << getGUID() << " , '" << x << "') \n";
		}


		for (auto &x : containerC)
		{
			x->save(myFile, guid);
		}
	}
}
