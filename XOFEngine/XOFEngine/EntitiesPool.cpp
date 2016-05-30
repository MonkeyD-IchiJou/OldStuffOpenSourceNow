#include "EntitiesPool.h"
#include "Entity.h"

#include "TransformationC.h"

#include <sstream>
#include <fstream>
using std::ostream;
using std::ofstream;

namespace pp
{

	EntitiesPool::EntitiesPool(const string& scene_state):
		scene_state(scene_state),
		entities(nullptr)
	{
	}


	EntitiesPool::~EntitiesPool()
	{
		destroyAllEntities();
	}

	void EntitiesPool::create(void)
	{
		// prevent memory leak
		destroyAllEntities();

		// create the entities dynamically
		entities = new Entity[MAX_ENTITY];

		// make sure all the entities know which scene they belong to
		// and their pools 
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			entities[i].bigDaddy = this;
			entities[i].setSceneTag(scene_state);
		}
	}

	void EntitiesPool::update(const float & dt)
	{
		// do nothing
	}

	Entity * EntitiesPool::FetchEntity(void)
	{
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (entities[i].getGUID() == 0)
			{
				entities[i].setActive(true);
				return &entities[i];
			}
		}

		// worst case scenario
		return nullptr;
	}

	Entity * EntitiesPool::findEntity(const unsigned int & guid)
	{
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (entities[i].getTotalComponentSize() == 0)
			{
				break;
			}

			if (entities[i].getGUID() == guid)
			{
				return &entities[i];
			}
		}

		// worst case scenario
		return nullptr;
	}

	Entity * EntitiesPool::FindNotActiveEntity(const string & tag)
	{
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			Entity& e = entities[i];

			if (e.isActive() == false)
			{
				if (e.getGUID() == 0)
				{
					break;
				}

				if (e.isTag(tag))
				{
					// set it to active
					e.setActive(true);

					// same as its children 
					for (auto &x : e.children)
					{
						x->setActive(true);
					}

					return &entities[i];
				}
			}
		}

		// worst case scenario
		return nullptr;
	}

	void EntitiesPool::FindAllEntities(vector<Entity*>& r, const string & tag)
	{
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (entities[i].getTotalComponentSize() != 0)
			{
				if (entities[i].isTag(tag))
				{
					r.push_back(&entities[i]);
				}

			}
			else
			{
				break;
			}
		}
	}

	Entity * EntitiesPool::findEntity(const string & name)
	{
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (entities[i].getGUID() == 0)
			{
				break;
			}

			if (entities[i].getEntityName() == name)
			{
				return &entities[i];
			}
		}

		// worst case scenario
		return nullptr;
	}

	void EntitiesPool::debug(void)
	{
		std::vector<Entity*> debug;
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (entities[i].getTotalComponentSize() != 0) debug.push_back(&entities[i]);
			else break;
		}

		debug.clear();
	}

	void EntitiesPool::destroyAllEntities(void)
	{
		if (entities)
		{
			for (int i = 0; i < MAX_ENTITY; ++i)
			{
				entities[i].destroy();
			}

			delete[]entities;
			entities = nullptr;
		}
	}

	// save the whole entities baby
	void EntitiesPool::save(const string& file_path)
	{

	}
}
