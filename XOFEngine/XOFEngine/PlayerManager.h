#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "enumc.h"
#include "MathsHeader.h"

#include "Frustum.h"

namespace pp {

	class Entity;
	class ComponentsPool;

	struct assInfo
	{
		assInfo() : distance(4.f)
		{

		}

		vec3f assPos;
		vec3f direction;
		vec3f oldAssPos;
		float distance;

		vec3f addedVel;
	};

	class PlayerManager
	{
	public:

		// Player body parts and which one to control
		Entity* player[FULLBODY];
		Entity* playerChild[LASTDRAGONCHILD];

		PLAYER_CONTROL_STATE PlayerControlState;
		LEADER_HEAD_COMMAND headCommandState;

		assInfo dragonass[FULLBODY];

		void CreatePlayer(void);
		void DestroyPlayer(void);

		// Update entities component 
		void Update(const float& dt);

		void draw(void);
		void drawDepth(void);

		void lateUpdate(const float& dt);

		void gravitySet(const vec3f & gravity);

		void renderLine(void);

		void attackImpulse(const vec3f & dinopos);

		vec3f vel, gravity;

		bool dead, endgame;

		ComponentsPool* allComponents;

		void Restart();

		void DinoSeePlayer(const mat4f& vp, bool *seeplayer);

		// Singleton class implementation
		static inline PlayerManager* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new PlayerManager();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

		bool updateMah, isHeadMoving, isTailMoving;

	private:

		PlayerManager();
		~PlayerManager();

		void headChildInit(void);
		void Body1ChildInit(void);
		void Body2ChildInit(void);
		void TailsChildInit(void);

		CFrustum* frustumHandle;

		static PlayerManager* s_instance;

		

	};
}

#endif