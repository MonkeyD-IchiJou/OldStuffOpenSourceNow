#ifndef ENTITIES_POOL_H
#define ENTITIES_POOL_H

#include <string>
#include <vector>

#include "MathsHeader.h"
using std::vector;
using std::string;

namespace pp
{
	class Entity;

	class EntitiesPool
	{
	public:
		// constructor take in the scene that this belong to
		EntitiesPool(const string& sceneName);
		~EntitiesPool(void);

		// create all the entities
		void create(void);

		// update all the entities
		void update(const float & dt);

		// destroy it 
		void destroyAllEntities(void);

		// debug only
		void debug(void);

		// save the whole entities baby
		void save(const string& file_path);

		// find the entity based on the unique guid
		Entity* findEntity(const unsigned int& guid);

		// find the enity based on its name
		Entity* findEntity(const string &name);

		// entity vector will fill up with the special tags
		void FindAllEntities(vector<Entity*>& r, const string & tag);

		// will return the entity if it doesnt have any component yet
		Entity* FetchEntity(void);

		// find the entity that is not active .. with special tag
		Entity* FindNotActiveEntity(const string &tag);

	private:
		string scene_state;
		Entity* entities; // all the entities
	};

}

#endif

