#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <fstream>

#include "enumc.h"
#include "MathsHeader.h"

using std::string;
using std::ofstream;

namespace pp
{
	class Component;
	class TransformationC;
	class EntitiesPool;

	class Entity
	{
	public:

		Entity(void);
		virtual ~Entity(void);

		// every entity will have its own update function
		virtual void update(const float& dt);

		// add component
		void AddComponent(Component *l_component);

		// find the specific type of the component
		Component* findComponent(COMPONENT_TYPE t);

		// find the specific component, and then return the original class type of it
		template<typename T>
		T * findComponentT(void)
		{
			for (auto &x : containerC)
			{
				if (T* temp = dynamic_cast<T*>(x))
				{
					return temp;
				}
			}

			return nullptr;
		}

		// find all the specific component, and then return the original class type of it
		template<typename T>
		std::vector<T*> findAllComponentT(void)
		{
			std::vector<T*> allC;

			for (auto &x : containerC)
			{
				if (T* temp = dynamic_cast<T*>(x))
				{
					allC.push_back(temp);
				}
			}

			return allC;
		}

		// getter for guid
		unsigned int getGUID(void);
		// setter for guid
		void setGUID(const unsigned int &id);

		// setter for active
		void setActive(const bool &active);
		// getter for active
		bool isActive(void);

		// setter for parents
		void setParent(Entity* parent);
		// getter for parents
		Entity* getParent(void);

		// setter for child
		void setChild(Entity* child);

		// inform the component/s to update in the next frame ( for once )
		void resetUpdateFlag(COMPONENT_TYPE t);

		// setter for scenetag
		void setSceneTag(const string& tag);
		// getter for scenetag
		string getSceneTag(void) const;

		// setter for entity name
		inline void setEntityName(const string &n) { entityName = n; }
		// getter for enttiy name
		inline string getEntityName(void) const { return entityName; }

		// set the tag for this entity
		void setTag(const string &n);
		// check whether this entity got this tag or not
		bool isTag(const string &tag);

		// get all the tag in this entity
		std::vector<string>& getTag(void);

		// destroy all the component (delete)
		void destroy(void);

		// return the size of the component
		int getTotalComponentSize(void);

		// every entity must have one transformation
		TransformationC* transformC;

		// entity save all his components
		void save(ofstream& myFile);

		// every Entity will have its own chirldren (by default is nothing) SceneGraph
		std::vector<Entity*> children;

		// the entities pool where its belong to
		EntitiesPool* bigDaddy;

		// add without setting parent
		inline void pureAddComponent(Component *l_component) { containerC.push_back(l_component); };

		void pureDestroy(void);

	protected:

		// this entity is belonged to which scene
		string scenetag;

		// check whether this entity is active or not
		// if inactive will not update the components
		bool active;

		// each entity is unique
		unsigned int guid;

		// the name of the entity
		string entityName;

		// every Entity will have its own component container
		// store all the components in this entity
		std::vector<Component*> containerC;

		// every Entity will have its own parent (by default is NULL) SceneGraph
		Entity* parent;

		// special tag to differentiate this entity
		std::vector<string> tags;

		// if entity is active then true. else false
		void componentsUpdateFlagUpdate(void);
	};
}

#endif

