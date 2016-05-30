#include "PlayerManager.h"
#include "Entity.h"
#include "TransformationC.h"
#include "MeshRendererC.h"
#include "SphereColliderC.h"
#include "AABB.h"
#include "MeshColliderC.h"
#include "EllipsoidColliderC.h"
#include "CameraC.h"
#include "ScriptC.h"
#include "LineRendererC.h"

#include "utils.h"
#include "ComponentsPool.h"

namespace pp
{
	PlayerManager* PlayerManager::s_instance = nullptr;

	PlayerManager::PlayerManager(void) : 
		PlayerControlState(HEAD), 
		headCommandState(ONYOUROWN), 
		updateMah(true), 
		allComponents(nullptr), 
		isTailMoving(false), 
		isHeadMoving(false), 
		dead (false),
		endgame(false),
		frustumHandle(nullptr)
	{
		ZERO_MEM(player);
		ZERO_MEM(playerChild);
		ZERO_MEM(dragonass);
		
	}

	PlayerManager::~PlayerManager(void)
	{
	}

	void PlayerManager::DinoSeePlayer(const mat4f& vp, bool *seeplayer)
	{
		frustumHandle->setVP(vp);

		for (int i = 0; i < TAIL1; ++i)
		{
			seeplayer[i] = frustumHandle->SphereIntersection(player[i]->transformC->localPosition, 5.f);
		}
	}

	void PlayerManager::CreatePlayer(void)
	{
		DestroyPlayer();

		frustumHandle = new CFrustum();

		if (allComponents != nullptr)
		{
			allComponents->destroyAllComponents();
			delete allComponents;
			allComponents = nullptr;
		}
		// second is all the components pool
		allComponents = new ComponentsPool("player de");
		allComponents->create();

		for (int i = 0; i < FULLBODY; ++i)
		{
			player[i] = new Entity();
			player[i]->setGUID(i + 1);
			player[i]->setActive(true);
			player[i]->setTag("player");

			player[i]->transformC = allComponents->FetchTransformC();
			TransformationC* t = player[i]->transformC;
			player[i]->AddComponent(t);
			t->position.Set( -20.f + i * 5.f, 10.f , -6.f);
			t->rotation.Set(0, 0, 0);

			EllipsoidColliderC* ec = allComponents->FetchEllipsoidColliderC();
			player[i]->AddComponent(ec);
			ec->eRadius.Set(1.6f, 2.6f, 1.6f);
			ec->setTag("player");

			if (i < 4)
			{
				MeshColliderC* mc = allComponents->FetchMeshColliderC();
				player[i]->AddComponent(mc);

				AABB* aabb = allComponents->FetchAABBC();
				player[i]->AddComponent(aabb);
				aabb->guid = 1;
				aabb->setHalfSize(vec3f(0, 0, 0));
				aabb->setPos(vec3f(0, 0, 0));
				aabb->setTag("player");
			}

			LineRendererC* linem = allComponents->FetchLineRendererC();
			player[i]->AddComponent(linem);

			MeshRendererC* mesh = allComponents->FetchMeshRendererC();
			player[i]->AddComponent(mesh);
			mesh->meshName = "CUBE";
			mesh->color.Set(1.25f, 0.5f, 0.1f);
			mesh->emissive = 0.f;
			mesh->shininess = 64.f;

			SphereColliderC* sc = allComponents->FetchSphereColliderC();
			player[i]->AddComponent(sc);
			sc->setfradius(2.f);
			sc->setTag("MESHCULL");


			ScriptC* script = allComponents->FetchScriptC();
			player[i]->AddComponent(script);
		}

		player[HEAD]->setEntityName("DragonHead");
		player[HEAD]->setTag("DragonHead");
		player[HEAD]->transformC->scale.Set(2.5f, 2.5f, 3.f);
		player[HEAD]->findComponentT<AABB>()->setTag("Head");
		player[HEAD]->findComponentT<MeshRendererC>()->meshName = "DRAGONHEAD";
		player[HEAD]->findComponentT<MeshColliderC>()->setMeshName("CUBE");
		player[HEAD]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonHead.lua";
		player[HEAD]->findComponentT<EllipsoidColliderC>()->eRadius.Set(1.9f, 1.6f, 1.9f);

		player[BODY1]->setEntityName("DragonBody1");
		player[BODY1]->setTag("DragonBody1");
		player[BODY1]->transformC->scale.Set(2.f, 2.f, 2.f);
		player[BODY1]->findComponentT<AABB>()->setTag("Body");
		player[BODY1]->findComponentT<AABB>()->setHalfSize(vec3f(0.4f, 0.4f, 0.4f));
		player[BODY1]->findComponentT<MeshRendererC>()->meshName = "DRAGONBODY";
		player[BODY1]->findComponentT<MeshColliderC>()->setMeshName("DRAGONBODY");
		player[BODY1]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonBody1.lua";
		player[BODY1]->findComponentT<EllipsoidColliderC>()->eRadius.Set(1.7f, 1.525f, 1.7f);

		player[BODY2]->setEntityName("DragonBody2");
		player[BODY2]->setTag("DragonBody2");
		player[BODY2]->transformC->scale.Set(2.f, 2.f, 2.f);
		player[BODY2]->findComponentT<AABB>()->setTag("Body");
		player[BODY2]->findComponentT<AABB>()->setHalfSize(vec3f(0.4f, 0.4f, 0.4f));
		player[BODY2]->findComponentT<MeshRendererC>()->meshName = "DRAGONBODY2";
		player[BODY2]->findComponentT<MeshColliderC>()->setMeshName("DRAGONBODY2");
		player[BODY2]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonBody2.lua";
		player[BODY2]->findComponentT<EllipsoidColliderC>()->eRadius.Set(1.7f, 1.525f, 1.7f);

		player[TAIL]->setEntityName("DragonTail");
		player[TAIL]->setTag("DragonTail");
		player[TAIL]->transformC->scale.Set(2.f, 2.f, 2.f);
		player[TAIL]->findComponentT<AABB>()->setTag("Tail");
		player[TAIL]->findComponentT<MeshRendererC>()->meshName = "DRAGONTAIL";
		player[TAIL]->findComponentT<MeshColliderC>()->setMeshName("CUBE");
		player[TAIL]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonTail.lua";
		player[TAIL]->findComponentT<EllipsoidColliderC>()->eRadius.Set(1.25f, 1.25f, 1.25f);
		
		player[TAIL1]->setEntityName("DragonTail1");
		player[TAIL1]->setTag("DragonTail1");
		player[TAIL1]->transformC->scale.Set(2.f, 2.f, 2.f);
		player[TAIL1]->findComponentT<MeshRendererC>()->meshName = "DRAGONTAIL1";
		player[TAIL1]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonTail1.lua";
		player[TAIL1]->findComponentT<EllipsoidColliderC>()->eRadius.Set(1.0f, 1.0f, 1.0f);

		player[TAIL2]->setEntityName("DragonTail2");
		player[TAIL2]->setTag("DragonTail2");
		player[TAIL2]->transformC->scale.Set(2.f, 2.f, 2.f);
		player[TAIL2]->findComponentT<MeshRendererC>()->meshName = "DRAGONTAIL2";
		player[TAIL2]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonTail2.lua";
		player[TAIL2]->findComponentT<EllipsoidColliderC>()->eRadius.Set(0.75f, 0.75f, 0.75f);

		player[TAIL3]->setEntityName("DragonTail3");
		player[TAIL3]->setTag("DragonTail3");
		player[TAIL3]->transformC->scale.Set(2.f, 2.f, 2.f);
		player[TAIL3]->findComponentT<MeshRendererC>()->meshName = "DRAGONTAIL3";
		player[TAIL3]->findComponentT<ScriptC>()->file_path = "Content//scripts//DragonTail3.lua";
		player[TAIL3]->findComponentT<EllipsoidColliderC>()->eRadius.Set(0.5f, 0.5f, 0.5f);

		dragonass[HEAD].distance = 5.f;
		dragonass[BODY1].distance = 6.0f;
		dragonass[BODY2].distance = 6.0f;
		dragonass[TAIL].distance = 2.1f;
		dragonass[TAIL1].distance = 1.1f;
		dragonass[TAIL2].distance = 0.8f;
		dragonass[TAIL3].distance = 0.5f;

		headChildInit();
		Body1ChildInit();
		Body2ChildInit();
		TailsChildInit();
	}

	void PlayerManager::headChildInit(void)
	{
		playerChild[TEETH] = new Entity();
		playerChild[TEETH]->setGUID(1001);
		playerChild[TEETH]->setActive(true);
		playerChild[TEETH]->setTag("player");
		playerChild[TEETH]->setTag("teeth");
		playerChild[TEETH]->setParent(player[HEAD]);
		player[HEAD]->setChild(playerChild[TEETH]);

		playerChild[TEETH]->transformC = allComponents->FetchTransformC();
		TransformationC* t = playerChild[TEETH]->transformC;
		playerChild[TEETH]->AddComponent(t);
		t->scale.Set(2.5f, 2.5f, 3.f);

		SphereColliderC* sc = allComponents->FetchSphereColliderC();
		playerChild[TEETH]->AddComponent(sc);
		sc->setfradius(2);

		MeshRendererC* mesh = allComponents->FetchMeshRendererC();
		playerChild[TEETH]->AddComponent(mesh);
		mesh->meshName = "DRAGONTEETH";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 64.f;



		// horns
		playerChild[HEADHORN] = new Entity();
		playerChild[HEADHORN]->setGUID(1001);
		playerChild[HEADHORN]->setActive(true);
		playerChild[HEADHORN]->setTag("player");
		playerChild[HEADHORN]->setTag("horn");
		playerChild[HEADHORN]->setParent(player[HEAD]);
		player[HEAD]->setChild(playerChild[HEADHORN]);

		playerChild[HEADHORN]->transformC = allComponents->FetchTransformC();
		t = playerChild[HEADHORN]->transformC;
		playerChild[HEADHORN]->AddComponent(t);
		t->scale.Set(2.5f, 2.5f, 3.f);

		sc = allComponents->FetchSphereColliderC();
		playerChild[HEADHORN]->AddComponent(sc);
		sc->setfradius(2);

		mesh = allComponents->FetchMeshRendererC();
		playerChild[HEADHORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONHEADHORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;


		// power cube
		playerChild[POWERCUBE] = new Entity();
		playerChild[POWERCUBE]->setGUID(1001);
		playerChild[POWERCUBE]->setActive(true);
		playerChild[POWERCUBE]->setTag("player");
		playerChild[POWERCUBE]->setTag("powercube");
		playerChild[POWERCUBE]->setParent(player[HEAD]);
		player[HEAD]->setChild(playerChild[POWERCUBE]);

		playerChild[POWERCUBE]->transformC = allComponents->FetchTransformC();
		t = playerChild[POWERCUBE]->transformC;
		playerChild[POWERCUBE]->AddComponent(t);
		t->scale.Set(2.5f, 2.5f, 3.f);

		sc = allComponents->FetchSphereColliderC();
		playerChild[POWERCUBE]->AddComponent(sc);
		sc->setfradius(2);

		mesh = allComponents->FetchMeshRendererC();
		playerChild[POWERCUBE]->AddComponent(mesh);
		mesh->meshName = "DRAGONPOWERCUBE";
		mesh->color.Set(0.7f, 0.7f, 1.0f);
		mesh->emissive = 1.f;
		mesh->shininess = 32.f;
	}

	void PlayerManager::Body1ChildInit(void)
	{
		// horns
		playerChild[BODY1HORN] = new Entity();
		playerChild[BODY1HORN]->setGUID(1001);
		playerChild[BODY1HORN]->setActive(true);
		playerChild[BODY1HORN]->setTag("player");
		playerChild[BODY1HORN]->setTag("horn");
		playerChild[BODY1HORN]->setParent(player[BODY1]);
		player[BODY1]->setChild(playerChild[BODY1HORN]);

		playerChild[BODY1HORN]->transformC = allComponents->FetchTransformC();
		TransformationC * t = playerChild[BODY1HORN]->transformC;
		playerChild[BODY1HORN]->AddComponent(t);
		t->scale.Set(2.f, 2.f, 2.f);

		SphereColliderC* sc = allComponents->FetchSphereColliderC();
		playerChild[BODY1HORN]->AddComponent(sc);
		sc->setfradius(2);

		MeshRendererC* mesh = allComponents->FetchMeshRendererC();
		playerChild[BODY1HORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONBODY1HORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;
	}

	void PlayerManager::Body2ChildInit(void)
	{
		// horns
		playerChild[BODY2HORN] = new Entity();
		playerChild[BODY2HORN]->setGUID(1001);
		playerChild[BODY2HORN]->setActive(true);
		playerChild[BODY2HORN]->setTag("player");
		playerChild[BODY2HORN]->setTag("horn");
		playerChild[BODY2HORN]->setParent(player[BODY2]);
		player[BODY2]->setChild(playerChild[BODY2HORN]);

		playerChild[BODY2HORN]->transformC = allComponents->FetchTransformC();
		TransformationC * t = playerChild[BODY2HORN]->transformC;
		playerChild[BODY2HORN]->AddComponent(t);
		t->scale.Set(2.f, 2.f, 2.f);

		SphereColliderC* sc = allComponents->FetchSphereColliderC();
		playerChild[BODY2HORN]->AddComponent(sc);
		sc->setfradius(2);

		MeshRendererC* mesh = allComponents->FetchMeshRendererC();
		playerChild[BODY2HORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONBODY2HORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;
	}

	void PlayerManager::TailsChildInit(void)
	{
		// horns
		playerChild[TAILHORN] = new Entity();
		playerChild[TAILHORN]->setGUID(1001);
		playerChild[TAILHORN]->setActive(true);
		playerChild[TAILHORN]->setTag("player");
		playerChild[TAILHORN]->setTag("horn");
		playerChild[TAILHORN]->setParent(player[TAIL]);
		player[TAIL]->setChild(playerChild[TAILHORN]);

		playerChild[TAILHORN]->transformC = allComponents->FetchTransformC();
		TransformationC * t = playerChild[TAILHORN]->transformC;
		playerChild[TAILHORN]->AddComponent(t);
		t->scale.Set(2.f, 2.f, 2.f);

		SphereColliderC* sc = allComponents->FetchSphereColliderC();
		playerChild[TAILHORN]->AddComponent(sc);
		sc->setfradius(2);

		MeshRendererC* mesh = allComponents->FetchMeshRendererC();
		playerChild[TAILHORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONTAILHORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;

		// tail1horn
		playerChild[TAIL1HORN] = new Entity();
		playerChild[TAIL1HORN]->setGUID(1001);
		playerChild[TAIL1HORN]->setActive(true);
		playerChild[TAIL1HORN]->setTag("player");
		playerChild[TAIL1HORN]->setTag("tail1horn");
		playerChild[TAIL1HORN]->setParent(player[TAIL1]);
		player[TAIL1]->setChild(playerChild[TAIL1HORN]);

		playerChild[TAIL1HORN]->transformC = allComponents->FetchTransformC();
		t = playerChild[TAIL1HORN]->transformC;
		playerChild[TAIL1HORN]->AddComponent(t);
		t->scale.Set(2.f, 2.f, 2.f);

		mesh = allComponents->FetchMeshRendererC();
		playerChild[TAIL1HORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONTAIL1HORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;

		// tail2horn
		playerChild[TAIL2HORN] = new Entity();
		playerChild[TAIL2HORN]->setGUID(1001);
		playerChild[TAIL2HORN]->setActive(true);
		playerChild[TAIL2HORN]->setTag("player");
		playerChild[TAIL2HORN]->setTag("tail2horn");
		playerChild[TAIL2HORN]->setParent(player[TAIL2]);
		player[TAIL2]->setChild(playerChild[TAIL2HORN]);

		playerChild[TAIL2HORN]->transformC = allComponents->FetchTransformC();
		t = playerChild[TAIL2HORN]->transformC;
		playerChild[TAIL2HORN]->AddComponent(t);
		t->scale.Set(2.f, 2.f, 2.f);

		mesh = allComponents->FetchMeshRendererC();
		playerChild[TAIL2HORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONTAIL2HORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;

		// TAIL3horn
		playerChild[TAIL3HORN] = new Entity();
		playerChild[TAIL3HORN]->setGUID(1001);
		playerChild[TAIL3HORN]->setActive(true);
		playerChild[TAIL3HORN]->setTag("player");
		playerChild[TAIL3HORN]->setTag("tail3horn");
		playerChild[TAIL3HORN]->setParent(player[TAIL3]);
		player[TAIL3]->setChild(playerChild[TAIL3HORN]);

		playerChild[TAIL3HORN]->transformC = allComponents->FetchTransformC();
		t = playerChild[TAIL3HORN]->transformC;
		playerChild[TAIL3HORN]->AddComponent(t);
		t->scale.Set(2.f, 2.f, 2.f);

		mesh = allComponents->FetchMeshRendererC();
		playerChild[TAIL3HORN]->AddComponent(mesh);
		mesh->meshName = "DRAGONTAIL3HORN";
		mesh->color.Set(0.1f, 0.1f, 0.1f);
		mesh->emissive = 0.f;
		mesh->shininess = 32.f;

	}

	void PlayerManager::attackImpulse(const vec3f & dinopos)
	{
		headCommandState = ONYOUROWN;

		Entity* e = nullptr;
		EllipsoidColliderC* ellipc = nullptr;

		for (int i = 0; i < TAIL; ++i)
		{
			e = player[i];

			vec3f dir = (e->transformC->position - dinopos);
			float dist = dir.lengthSquared();
			
			ellipc = e->findComponentT<EllipsoidColliderC>();

			if (dist < 8.f * 8.f)
			{
				vec3f& eVel = ellipc->R3Attack;

				ellipc->R3Attack = dir.normalize() * 1.5f;
			}
			
		}
	}

	void Friction(vec3f & vel)
	{
		vec3f frictionDir = vel.normalized()* 0.025f;

		vec3f oldVel = vel;
		vel = vel - frictionDir;

		if (vel.dot(oldVel) < 0.0f)
		{
			vel.SetZero();
		}
	}

	void PlayerManager::Update(const float& dt)
	{
		if (updateMah)
		{
			Entity* e = nullptr;
			EllipsoidColliderC* ellipc = nullptr;
			TransformationC* transform = nullptr;

			allComponents->updateAllComponents(dt);

			for (int i = 0; i < FULLBODY; ++i)
			{
				e = player[i];
				ellipc = e->findComponentT<EllipsoidColliderC>();
				transform = e->transformC;
				CameraC* c = ComponentsPool::cameraComponent;
				vec3f& eVel = ellipc->R3Velocity;

				if (i == HEAD)
				{
					eVel.IsZero() ? isHeadMoving = false : isHeadMoving = true;
				}

				else if (i == TAIL)
				{
					eVel.IsZero() ? isTailMoving = false : isTailMoving = true;
				}

				// my tails is always facing the right direction
				// if it is the control state then go
				// if the head is asking them to gather .. pls
				if (i > TAIL || i == PlayerControlState || headCommandState != ONYOUROWN)
				{
					vec3f tempV = eVel + ellipc->R3slidingDir + ellipc->R3gravity;
					tempV.y = transform->position.y - transform->oldposy;
					
					if (tempV.lengthSquared() > 0.2f * 0.2f)
					{
						tempV.normalize();
						dragonass[i].assPos = transform->position - tempV * dragonass[i].distance;
						e->transformC->LookAtAll(tempV, 1);
					}

					transform->oldposy = transform->position.y;
				}

				Friction(ellipc->R3Attack);
			}
		}
	}

	void PlayerManager::lateUpdate(const float& dt)
	{
		if (updateMah)
		{
			CameraC* c = ComponentsPool::cameraComponent;
			allComponents->updatePrevMVP(c->getView(), c->getProjection());
		}
	}

	void PlayerManager::gravitySet(const vec3f & gravity)
	{
	}

	void PlayerManager::renderLine(void)
	{
		if (updateMah)
		{
			if (headCommandState == FOLLOWME)
			{
				for (int i = 0; i < TAIL1; ++i)
				{
					player[i]->findComponentT<LineRendererC>()->draw();
				}
			}

			for (int i = TAIL1; i < FULLBODY; ++i)
			{
				player[i]->findComponentT<LineRendererC>()->draw();
			}
		}
	}

	void PlayerManager::Restart()
	{
		ZERO_MEM(dragonass);

		PlayerControlState = HEAD;
		headCommandState = ONYOUROWN;
		updateMah = true;
		isTailMoving = false;
		isHeadMoving = false;
		dead = false;
		endgame = false;

		CreatePlayer();
	}

	void PlayerManager::draw(void)
	{
		if (updateMah)
		{
			allComponents->renderMesh();
		}
	}

	void PlayerManager::drawDepth(void)
	{
		if (updateMah)
		{
			allComponents->renderMeshDepth();
		}
	}

	void PlayerManager::DestroyPlayer(void)
	{
		for (int i = 0; i < FULLBODY; ++i)
		{
			if (player[i])
			{
				player[i]->pureDestroy();
				delete player[i];
				player[i] = nullptr;
			}
		}


		for (int i = 0; i < LASTDRAGONCHILD; ++i)
		{
			if (playerChild[i])
			{
				playerChild[i]->pureDestroy();
				delete playerChild[i];
				playerChild[i] = nullptr;
			}
		}

		if (frustumHandle)
		{
			delete frustumHandle;
			frustumHandle = nullptr;
		}
	}

}