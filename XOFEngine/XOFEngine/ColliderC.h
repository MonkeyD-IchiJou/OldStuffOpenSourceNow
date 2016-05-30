#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

#include <vector>

namespace pp
{
	enum COLLIDER_TYPE
	{
		SPHERE_TYPE = 0,
		AABB_TYPE,
		ELLIPSOID_TYPE,
		MESH_TYPE,
		NO_COLLIDER
	};

	class ColliderC :
		public Component
	{
	public:
		ColliderC(COLLIDER_TYPE type);
		virtual ~ColliderC(void);

		virtual void update(const float& dt) override;
		virtual void draw(void) const = 0; // debug purpose
		virtual void save(ofstream& myFile, const unsigned int & guid) override;

		inline bool isTag(const std::string & tag) 
		{
			for (auto &x : this->tag)
			{
				if (x == tag)
				{
					return true;
				}
			}

			return false;
		}

		inline void setTag(const std::string & tag)
		{
			this->tag.push_back(tag);
		}

		inline void setCollide(const bool &c) { collide = c; }
		inline bool isCollide(void) const { return collide; }

	public:
		COLLIDER_TYPE type;
		std::vector<std::string> tag; // to differentiate the collider 
		unsigned int guid; // must be unique

	protected:
		bool collide;
	};
}

#endif

