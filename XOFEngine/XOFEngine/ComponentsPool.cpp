#include "ComponentsPool.h"

#include "componentsH_dclr.h"

#include "GLFW_Window.h"

#include "TESTPLANE.h"

#include "Entity.h"

#include "PlayerManager.h"
#include "Mouse.h"

typedef unsigned int uint32;
#define in(a) ((uint32&) a)

namespace pp
{
	PlayerManager* ComponentsPool::playerHandle = nullptr;
	CameraC* ComponentsPool::cameraComponent = nullptr;

	ComponentsPool::ComponentsPool(const string& sceneName) :
		scenename(scenename),
		transformComponents(nullptr),
		MeshRendererComponents(nullptr),
		dirlightComponents(nullptr),
		pointlightComponents(nullptr),
		scriptComponents(nullptr),
		guitextComponents(nullptr),
		spherecolliderComponents(nullptr),
		aabbComponents(nullptr),
		bulletComponents(nullptr),
		meshcolliderComponents(nullptr),
		triggerComponents(nullptr),
		ellipsoidcolliderComponents(nullptr),
		CanvasComponents(nullptr),
		lineRendererComponents(nullptr),
		dinoAIComponents(nullptr)
	{
		ZERO_MEM(CSize);
		if (playerHandle == nullptr ) playerHandle = PlayerManager::getInstance();
	}

	ComponentsPool::~ComponentsPool(void)
	{
		destroyAllComponents();
	}

	void ComponentsPool::create(void)
	{
		// prevent memory leak
		destroyAllComponents();

		transformComponents = new TransformationC[MAX_ENTITY];
		MeshRendererComponents = new MeshRendererC[MAX_ENTITY];
		dirlightComponents = new DirLightC[MAX_ENTITY];
		pointlightComponents = new PointLightC[MAX_ENTITY];
		scriptComponents = new ScriptC[MAX_ENTITY];
		guitextComponents = new GUIText[MAX_ENTITY];
		spherecolliderComponents = new SphereColliderC[MAX_ENTITY];
		aabbComponents = new AABB[MAX_ENTITY];
		bulletComponents = new BulletC[MAX_ENTITY];
		meshcolliderComponents = new MeshColliderC[MAX_ENTITY];
		ellipsoidcolliderComponents = new EllipsoidColliderC[MAX_ENTITY];
		triggerComponents = new TriggerC[MAX_ENTITY];
		dinoAIComponents = new DinoAIC[MAX_ENTITY];
		CanvasComponents = new CanvasC[MAX_ENTITY];
		lineRendererComponents = new LineRendererC[MAX_ENTITY];

		// if my main camera havent get initialise .. do it once
		if (cameraComponent == nullptr)
		{
			cameraComponent = new CameraC();
			GLFW_Window *windowHandle = GLFW_Window::getInstance();
			cameraComponent->setAspect(static_cast<double>(windowHandle->getWindowWidth()) / static_cast<double>(windowHandle->getWindowHeight()));
		}
	}

	void ComponentsPool::updateAllComponents(const float & dt)
	{
		// NOTE ::	component must have owners before carry on
		//			transformation components always update last 


		// script update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::SCRIPT]; i++)
		{
			scriptComponents[i].update(dt);
		}

		// dino ai update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::DINOAI]; i++)
		{
			dinoAIComponents[i].update(dt);
		}

		// dirlight update 
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::DIRLIGHT]; ++i)
		{
			dirlightComponents[i].update(dt);
		}

		// mesh renderer update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHRENDERER]; ++i)
		{
			MeshRendererComponents[i].update(dt);
		}

		// triggerC update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::TRIGGER]; ++i)
		{
			triggerComponents[i].update(dt);
		}

		// transform update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::TRANSFORM]; ++i)
		{
			transformComponents[i].update(dt);
		}

		// mesh collider update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHCOLLIDER]; ++i)
		{
			meshcolliderComponents[i].update(dt);
		}

		// ellipsoid collider update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::ELLIPSOIDCOLLIDER]; ++i)
		{
			ellipsoidcolliderComponents[i].update(dt);
		}


		// sphere collider update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::SPHERECOLLIDER]; ++i)
		{
			spherecolliderComponents[i].update(dt);
		}

		// gui text update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::GUITEXT]; ++i)
		{
			guitextComponents[i].update(dt);
		}

		// point light update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::POINTLIGHT]; ++i)
		{
			pointlightComponents[i].update(dt);
		}

		
		// collider AABB update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]; ++i)
		{
			aabbComponents[i].update(dt);
		}

		// canvas update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::CANVAS]; ++i)
		{
			CanvasComponents[i].update(dt);
		}

		// line renderer update
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::LINERENDERER]; ++i)
		{
			lineRendererComponents[i].update(dt);
		}

		/*MousePicker* handle = MousePicker::getInstance();
		vec3f intersectpoint;
		float t = 0.f;
		vec3f campos = getRenderCamera()->position;

		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]; ++i)
		{
		bool hit = handle->RayAABBIntersection(aabbComponents[i], intersectpoint, t);
		if (hit)
		{
		std::cout << aabbComponents[i].getOwner()->getGUID() << std::endl;
		break;
		}
		}*/

		//// fastest sorting
		//std::map<float, AABB*> sorted;
		//for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]; ++i)
		//{
		//	float distance = (campos - aabbComponents[i].getRPos()).lengthSquared();
		//	sorted[distance] = &aabbComponents[i];
		//}
		//for (std::map<float, AABB*>::iterator it = sorted.begin(); it != sorted.end(); ++it)
		//{
		//	AABB& aabb = *it->second;
		//	bool hit = handle->RayAABBIntersection(aabb, intersectpoint, t);
		//	if (hit)
		//	{
		//		std::cout << aabb.getOwner()->getGUID() << std::endl;
		//		break;
		//	}
		//}


	}

	void ComponentsPool::updatePrevMVP(const mat4f & prevView, const mat4f & prevProj)
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::TRANSFORM]; ++i)
		{
			transformComponents[i].updatePrevMat4(prevView, prevProj);
		}
	}

	void ComponentsPool::updateALLCamAspect(const double & aspect)
	{
		cameraComponent->setAspect(aspect);
	}

	void ComponentsPool::renderMesh(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHRENDERER]; ++i)
		{
			MeshRendererComponents[i].draw();
		}
	}

	void ComponentsPool::renderMeshDepth(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHRENDERER]; ++i)
		{
			MeshRendererComponents[i].drawDepth();
		}
	}

	void ComponentsPool::renderSphereCollider(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::SPHERECOLLIDER]; ++i)
		{
			spherecolliderComponents[i].draw();
		}
	}

	void ComponentsPool::renderAABB(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]; ++i)
		{
			aabbComponents[i].draw();
		}
	}

	void ComponentsPool::renderMeshCollider(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHCOLLIDER]; ++i)
		{
			meshcolliderComponents[i].draw();
		}
	}

	void ComponentsPool::renderEllipsoidCollider(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::ELLIPSOIDCOLLIDER]; ++i)
		{
			ellipsoidcolliderComponents[i].draw();
		}
	}

	void ComponentsPool::drawALLText(void) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::GUITEXT]; ++i)
		{
			guitextComponents[i].draw();
		}
	}

	void ComponentsPool::loadGUITex(void)
	{
		CameraC* cam = cameraComponent;

		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::GUITEXT]; ++i)
		{
			guitextComponents[i].setCamHandle(cam);
			guitextComponents[i].loadDynamic();

			guitextComponents[i].update(0.01f);
		}
	}

	void ComponentsPool::ReadPointLightsInfo(const bool & pon) const
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::POINTLIGHT]; ++i)
		{
			pointlightComponents[i].ShaderReadInfo(pon);
		}
	}

	void ComponentsPool::AABBvsAABBs(AABB& own, const std::string& tagToCollide)
	{
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]; ++i)
		{
			AABB& aabb = aabbComponents[i];

			// cannot be the same
			if (aabb.getOwner() == own.getOwner())
			{
				continue;
			}

			if (aabb.isTag(tagToCollide))
			{
				AABB::INTERSECTION_TYPE intersectinfo = own.intersect(aabb);
				if (intersectinfo == AABB::INTERSECTION_TYPE::INSIDE || intersectinfo == AABB::INTERSECTION_TYPE::INTERSECT)
				{
					break;
				}
			}
		}
	}

	void ComponentsPool::cursorPosVSAABBs(void)
	{
		Mouse* mouse = Mouse::getInstance();
		vec3f cursorPos(mouse->cursorPosFont.x, mouse->cursorPosFont.y, 0);

		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]; ++i)
		{
			AABB& aabb = aabbComponents[i];

			if (aabb.isTag("GUI"))
			{
				aabb.pointVSAABB(cursorPos);
			}
		}

	}

	void ComponentsPool::EllipsoidCollideAndSlide(EllipsoidColliderC * colPackage, const float & dt)
	{
		//// Do collision detection:
		// init
		vec3f espaceV = colPackage->espaceV();

		// collision checking update

		// R3Pos is the local position .. vel from script take pls
		colPackage->updateR3PosAndVel();

		// calculate position and velocity in eSpace
		// from here ......
		vec3f eSpacePosition = colPackage->R3Position * espaceV;
		vec3f eSpaceVelocity = (colPackage->R3Velocity  + colPackage->R3Attack ) * espaceV;

		// Iterate until we have our final position.
		colPackage->collisionRecursionDepth = 0;
		vec3f finalPosition = collideWithWorld(eSpacePosition, eSpaceVelocity, colPackage, false, dt);
		// ... to here

		// Add gravity pull:
		// To remove gravity uncomment from here .....
		// Set the new R3 position (convert back from eSpace to R3)
		colPackage->R3Position = finalPosition * colPackage->eRadius;

		eSpaceVelocity = colPackage->R3gravity * espaceV;

		// Iterate until we have our final position.
		colPackage->collisionRecursionDepth = 0;
		finalPosition = collideWithWorld(finalPosition, eSpaceVelocity * dt, colPackage, true, dt);
		// ... to here


		// Convert final result back to R3:
		finalPosition = finalPosition * colPackage->eRadius;
		// Move the entity (application specific function)
		colPackage->updateFinalPos(finalPosition);
	}

	


	/* all fetching functions from here */

	TransformationC * ComponentsPool::FetchTransformC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (transformComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::TRANSFORM]++;
				transformComponents[i].setDaddy(this);
				return &transformComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	MeshRendererC * ComponentsPool::FetchMeshRendererC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (MeshRendererComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::MESHRENDERER]++;
				MeshRendererComponents[i].setDaddy(this);
				return &MeshRendererComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	DirLightC * ComponentsPool::FetchDirlightC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (dirlightComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::DIRLIGHT]++;
				dirlightComponents[i].setDaddy(this);
				return &dirlightComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	DirLightC * ComponentsPool::getDirLight(void) const
	{
		return &dirlightComponents[0];
	}

	PointLightC * ComponentsPool::FetchPointlightC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (pointlightComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::POINTLIGHT]++;
				pointlightComponents[i].setDaddy(this);
				return &pointlightComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	ScriptC * ComponentsPool::FetchScriptC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (scriptComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::SCRIPT]++;
				scriptComponents[i].setDaddy(this);
				return &scriptComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	GUIText* ComponentsPool::FetchGUITextC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (guitextComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::GUITEXT]++;
				guitextComponents[i].setDaddy(this);
				return &guitextComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	SphereColliderC * ComponentsPool::FetchSphereColliderC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (spherecolliderComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::SPHERECOLLIDER]++;
				spherecolliderComponents[i].setDaddy(this);
				return &spherecolliderComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	AABB * ComponentsPool::FetchAABBC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (aabbComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::AABBCOLLIDER]++;
				aabbComponents[i].setDaddy(this);
				return &aabbComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	BulletC * ComponentsPool::FetchBulletC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (bulletComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::BULLET]++;
				bulletComponents[i].setDaddy(this);
				return &bulletComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	TriggerC* ComponentsPool::FetchTriggerC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (triggerComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::TRIGGER]++;
				triggerComponents[i].setDaddy(this);
				return &triggerComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	MeshColliderC* ComponentsPool::FetchMeshColliderC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (meshcolliderComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::MESHCOLLIDER]++;
				meshcolliderComponents[i].setDaddy(this);
				return &meshcolliderComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	EllipsoidColliderC* ComponentsPool::FetchEllipsoidColliderC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (ellipsoidcolliderComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::ELLIPSOIDCOLLIDER]++;
				ellipsoidcolliderComponents[i].setDaddy(this);
				return &ellipsoidcolliderComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	DinoAIC* ComponentsPool::FetchDinoAIC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (dinoAIComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::DINOAI]++;
				dinoAIComponents[i].setDaddy(this);
				return &dinoAIComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	CanvasC* ComponentsPool::FetchCanvas(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (CanvasComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::CANVAS]++;
				CanvasComponents[i].setDaddy(this);
				return &CanvasComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	LineRendererC * ComponentsPool::FetchLineRendererC(void)
	{
		// if the component has no owner .. then let it go
		for (int i = 0; i < MAX_ENTITY; ++i)
		{
			if (lineRendererComponents[i].getOwner() == nullptr)
			{
				CSize[COMPONENTS_ALL_TYPE::LINERENDERER]++;
				lineRendererComponents[i].setDaddy(this);
				return &lineRendererComponents[i];
			}
		}

		// worst case scenario .. 
		return nullptr;
	}

	const float unitsPerMeter = 100.0f;
	vec3f ComponentsPool::collideWithWorld(const vec3f & pos, const vec3f & vel, EllipsoidColliderC * packet, const bool & gravity, const float&dt)
	{
		// All hard-coded distances in this function is
		// scaled to fit the setting above..
		// Set this to match application scale..
		float unitScale = unitsPerMeter / 100.0f;
		float veryCloseDistance = 0.005f * unitScale;

		// do we need to worry?
		if (packet->collisionRecursionDepth > 5)
		{
			return pos;
		}

		// Ok, we need to worry:
		packet->velocity = vel; // in espace
		packet->updateNormalizeVelocity();
		packet->basePoint = pos; // in espace
		packet->foundCollision = false;

		// Check for collision (calls the collision routines)
		// Application specific!!
		// r3 coordinates
		// From here --
		if (gravity) EllipsoidVsTriMesh(packet, dt * dt);
		else EllipsoidVsTriMesh(packet, dt);
		// Till here --

		// gravity collision found init to false when it is only first iteration
		if (packet->collisionRecursionDepth == 0)
		{
			packet->R3slidingDir.SetZero();
			packet->gravitySliding = false;
			packet->foundCollisionGravity = false;
		}

		// If no collision we just move along the velocity
		if (packet->foundCollision == false)
		{
			return (pos + vel);
		}




		// *** Collision occured ***

		if (gravity)
		{
			packet->foundCollisionGravity = true;
		}

		// The original destination point
		vec3f destinationPoint = (pos + vel);
		vec3f newBasePoint = pos;

		// only update if we are not already very close
		// and if so we only move very close to intersection..not
		// to the exact spot.
		if (packet->nearestDistance >= veryCloseDistance)
		{
			vec3f V = vel;

			// set the length of this velocity vector
			if (!V.IsZero())
			{
				V.normalize() *= static_cast<float>(packet->nearestDistance) - veryCloseDistance;
			}
			else
			{
				V.SetZero();
			}

			//V.SetLength(packet->nearestDistanceveryCloseDistance);
			newBasePoint = packet->basePoint + V;

			// Adjust polygon intersection point (so sliding
			// plane will be unaffected by the fact that we
			// move slightly less than collision tells us)
			if (!V.IsZero())
			{
				V.normalize();
			}

			packet->intersectionPoint -= veryCloseDistance * V;
		}

		// Determine the sliding plane
		vec3f slidePlaneOrigin = packet->intersectionPoint;
		vec3f slidePlaneNormal = newBasePoint - packet->intersectionPoint;


		if (!slidePlaneNormal.IsZero())
		{
			slidePlaneNormal.normalize();
		}


		PLANE slidingPlane(slidePlaneOrigin, slidePlaneNormal);



		// Again, sorry about formatting.. but look carefully ;)
		packet->newDestinationPointGravity = destinationPoint - static_cast<float>(slidingPlane.signedDistanceTo(destinationPoint)) * slidePlaneNormal;

		// Generate the slide vec3f, which will become our new
		// velocity vec3f for the next iteration
		vec3f newVelocityVector3 = packet->newDestinationPointGravity - packet->intersectionPoint;

		
		// when it is sliding
		if (gravity == true)
		{
			packet->R3slidingDir = newVelocityVector3 * packet->eRadius;
			packet->gravitySliding = true;
		}

		// Recurse:
		// dont recurse if the new velocity is very small
		if (newVelocityVector3.length() < veryCloseDistance)
		{
			return newBasePoint;
		}

		packet->collisionRecursionDepth++;

		return collideWithWorld(newBasePoint, newVelocityVector3, packet, gravity, dt);
	}

	void ComponentsPool::EllipsoidVsTriMesh(EllipsoidColliderC * packet, const float &dt)
	{
		vec3f espaceV = packet->espaceV();
		const vec3f& R3vel = packet->R3Velocity + packet->R3Attack;
		bool turn = false;
		Entity* packetOwner = packet->getOwner();

		// those who have meshcollider .. come and check pls
		for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHCOLLIDER]; ++i)
		{
			turn = true;

			MeshColliderC& meshc = meshcolliderComponents[i];

			Entity* meshcOwner = meshc.getOwner();
			

			// cannot be the same owner
			if (packetOwner == meshcOwner)
			{
				continue;
			}

			bool continueMah = false;
			for (auto &x : packetOwner->children)
			{
				if (x == meshcOwner)
				{
					continueMah = true;
					break;
				}
			}

			if (continueMah) continue;

			std::vector<vec3f>& alltris = meshc.tris;

			for (auto it = alltris.begin(); it != alltris.end(); it += 3)
			{
				if (checkTriangle(packet, espaceV * (*(it)), espaceV * (*(it + 1)), espaceV * (*(it + 2))) && turn == true)
				{
					turn = false;
				}
			}
		}

		// next check with player
		playerHandle->allComponents->EllipsoidVsPlayerMesh(packet, dt);
	}

	void ComponentsPool::EllipsoidVsPlayerMesh(EllipsoidColliderC * packet, const float & dt)
	{
		// player cannot check with player body parts when the command state is follow me
		// head is not commanding the rest .. and it is a player
		if (packet->isTag("player") && playerHandle->headCommandState != FOLLOWME)
		{
			vec3f espaceV = packet->espaceV();
			const vec3f& R3vel = packet->R3Velocity + packet->R3Attack;
			bool turn = false;
			Entity* packetOwner = packet->getOwner();

			// those who have meshcollider .. come and check pls
			for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHCOLLIDER]; ++i)
			{
				turn = true;

				MeshColliderC& meshc = meshcolliderComponents[i];

				Entity* meshcOwner = meshc.getOwner();


				// cannot be the same owner
				if (packetOwner == meshcOwner)
				{
					continue;
				}

				bool continueMah = false;
				for (auto &x : packetOwner->children)
				{
					if (x == meshcOwner)
					{
						continueMah = true;
						break;
					}
				}

				if (continueMah) continue;

				std::vector<vec3f>& alltris = meshc.tris;

				for (auto it = alltris.begin(); it != alltris.end(); it += 3)
				{
					if (checkTriangle(packet, espaceV * (*(it)), espaceV * (*(it + 1)), espaceV * (*(it + 2))) && turn == true)
					{
						EllipsoidColliderC* ellip = meshcOwner->findComponentT<EllipsoidColliderC>();
						if (ellip)
						{
							ellip->R3Velocity = R3vel.normalized() * dt * 15.f;
							
						}

						turn = false;
					}
				}
			}
		}

		// if is not a player
		else if (!packet->isTag("player"))
		{
			vec3f espaceV = packet->espaceV();
			const vec3f& R3vel = packet->R3Velocity + packet->R3Attack;
			bool turn = false;
			Entity* packetOwner = packet->getOwner();

			// those who have meshcollider .. come and check pls
			for (int i = 0; i < CSize[COMPONENTS_ALL_TYPE::MESHCOLLIDER]; ++i)
			{
				turn = true;

				MeshColliderC& meshc = meshcolliderComponents[i];

				Entity* meshcOwner = meshc.getOwner();

				// cannot be the same owner
				if (packetOwner == meshcOwner)
				{
					continue;
				}

				bool continueMah = false;
				for (auto &x : packetOwner->children)
				{
					if (x == meshcOwner)
					{
						continueMah = true;
						break;
					}
				}

				if (continueMah) continue;

				std::vector<vec3f>& alltris = meshc.tris;

				for (auto it = alltris.begin(); it != alltris.end(); it += 3)
				{
					if (checkTriangle(packet, espaceV * (*(it)), espaceV * (*(it + 1)), espaceV * (*(it + 2))) && turn == true)
					{
						turn = false;
					}
				}
			}
		}
	}

	bool ComponentsPool::checkTriangle(EllipsoidColliderC * colPackage, const vec3f & p1, const vec3f & p2, const vec3f & p3)
	{
		// Make the plane containing this triangle.
		PLANE trianglePlane(p1, p2, p3);


		// Is triangle front-facing to the velocity vec3?
		// We only check front-facing triangles
		// (your choice of course)
		if (trianglePlane.isFrontFacingTo(colPackage->normalizedVelocity))
		{
			// Get interval of plane intersection:
			double t0, t1;
			bool embeddedInPlane = false;


			// Calculate the signed distance from sphere
			// position to triangle plane
			double signedDistToTrianglePlane = trianglePlane.signedDistanceTo(colPackage->basePoint);


			// cache this as we’re going to use it a few times below:
			float normalDotVelocity = trianglePlane.normal.dot(colPackage->velocity);


			// if sphere is travelling parrallel to the plane:
			if (normalDotVelocity == 0.0f)
			{
				if (fabs(signedDistToTrianglePlane) >= 1.0f)
				{
					// Sphere is not embedded in plane.
					// No collision possible:
					return false;
				}
				else
				{
					// sphere is embedded in plane.
					// It intersects in the whole range [0..1]
					embeddedInPlane = true;
					t0 = 0.0;
					t1 = 1.0;
				}

			}


			else
			{
				// N dot D is not 0. Calculate intersection interval:
				t0 = (-1.0 - signedDistToTrianglePlane) / normalDotVelocity;
				t1 = (1.0 - signedDistToTrianglePlane) / normalDotVelocity;


				// Swap so t0 < t1
				if (t0 > t1)
				{
					double temp = t1;
					t1 = t0;
					t0 = temp;
				}


				// Check that at least one result is within range:
				if (t0 > 1.0f || t1 < 0.0f)
				{
					// Both t values are outside values [0,1]
					// No collision possible:
					return false;
				}


				// Clamp to [0,1]
				if (t0 < 0.0) t0 = 0.0;
				if (t1 < 0.0) t1 = 0.0;
				if (t0 > 1.0) t0 = 1.0;
				if (t1 > 1.0) t1 = 1.0;
			}


			// OK, at this point we have two time values t0 and t1
			// between which the swept sphere intersects with the
			// triangle plane. If any collision is to occur it must
			// happen within this interval.
			vec3f collisionPoint;
			bool foundCollison = false;
			float t = 1.0;


			// First we check for the easy case - collision inside
			// the triangle. If this happens it must be at time t0
			// as this is when the sphere rests on the front side
			// of the triangle plane. Note, this can only happen if
			// the sphere is not embedded in the triangle plane.
			if (!embeddedInPlane)
			{
				vec3f planeIntersectionPoint = (colPackage->basePoint - trianglePlane.normal) + static_cast<float>(t0) * colPackage->velocity;
				if (checkPointInTriangle(planeIntersectionPoint, p1, p2, p3))
				{
					foundCollison = true;
					t = static_cast<float>(t0);
					collisionPoint = planeIntersectionPoint;
				}
			}


			// if we haven’t found a collision already we’ll have to
			// sweep sphere against points and edges of the triangle.
			// Note: A collision inside the triangle (the check above)
			// will always happen before a vertex or edge collision!
			// This is why we can skip the swept test if the above
			// gives a collision!
			if (foundCollison == false)
			{
				// some commonly used terms:
				vec3f velocity = colPackage->velocity;
				vec3f base = colPackage->basePoint;
				float velocitySquaredLength = velocity.lengthSquared();
				float a, b, c; // Params for equation
				float newT;

				// For each vertex or edge a quadratic equation have to
				// be solved. We parameterize this equation as
				// a*t^2 + b*t + c = 0 and below we calculate the
				// parameters a,b and c for each test.
				// Check against points:
				a = velocitySquaredLength;
				// P1
				b = 2.0f * (velocity.dot(base - p1));
				c = (p1 - base).lengthSquared() - 1.0f;
				if (getLowestRoot(a, b, c, t, &newT))
				{
					t = newT;
					foundCollison = true;
					collisionPoint = p1;
				}

				// P2
				b = 2.0f * (velocity.dot(base - p2));
				c = (p2 - base).lengthSquared() - 1.0f;
				if (getLowestRoot(a, b, c, t, &newT))
				{
					t = newT;
					foundCollison = true;
					collisionPoint = p2;
				}

				// P3
				b = 2.0f * (velocity.dot(base - p3));
				c = (p3 - base).lengthSquared() - 1.0f;

				if (getLowestRoot(a, b, c, t, &newT))
				{
					t = newT;
					foundCollison = true;
					collisionPoint = p3;
				}


				// Check agains edges:
				// p1 -> p2:
				vec3f edge = p2 - p1;
				vec3f baseToVertex = p1 - base;
				float edgeSquaredLength = edge.lengthSquared();
				float edgeDotVelocity = edge.dot(velocity);
				float edgeDotBaseToVertex = edge.dot(baseToVertex);

				// Calculate parameters for equation
				a = edgeSquaredLength*-velocitySquaredLength + edgeDotVelocity*edgeDotVelocity;

				b = edgeSquaredLength*(2.f * velocity.dot(baseToVertex)) - 2.0f*edgeDotVelocity*edgeDotBaseToVertex;

				c = edgeSquaredLength*(1.f - baseToVertex.lengthSquared()) + edgeDotBaseToVertex*edgeDotBaseToVertex;

				// Does the swept sphere collide against infinite edge?

				if (getLowestRoot(a, b, c, t, &newT))
				{
					// Check if intersection is within line segment:
					float f = (edgeDotVelocity*newT - edgeDotBaseToVertex) / edgeSquaredLength;
					if (f >= 0.0 && f <= 1.0)
					{
						// intersection took place within segment.
						t = newT;
						foundCollison = true;
						collisionPoint = p1 + f*edge;
					}
				}

				// p2 -> p3:
				edge = p3 - p2;

				baseToVertex = p2 - base;

				edgeSquaredLength = edge.lengthSquared();

				edgeDotVelocity = edge.dot(velocity);

				edgeDotBaseToVertex = edge.dot(baseToVertex);

				a = edgeSquaredLength*-velocitySquaredLength + edgeDotVelocity*edgeDotVelocity;

				b = edgeSquaredLength*(2.f * velocity.dot(baseToVertex)) - 2.0f*edgeDotVelocity*edgeDotBaseToVertex;

				c = edgeSquaredLength*(1.f - baseToVertex.lengthSquared()) + edgeDotBaseToVertex*edgeDotBaseToVertex;

				if (getLowestRoot(a, b, c, t, &newT))
				{
					float f = (edgeDotVelocity*newT - edgeDotBaseToVertex) / edgeSquaredLength;
					if (f >= 0.0f && f <= 1.0f)
					{
						t = newT;
						foundCollison = true;
						collisionPoint = p2 + f*edge;
					}
				}

				// p3 -> p1:
				edge = p1 - p3;
				baseToVertex = p3 - base;
				edgeSquaredLength = edge.lengthSquared();
				edgeDotVelocity = edge.dot(velocity);

				edgeDotBaseToVertex = edge.dot(baseToVertex);
				a = edgeSquaredLength*-velocitySquaredLength + edgeDotVelocity*edgeDotVelocity;

				b = edgeSquaredLength*(2.f * velocity.dot(baseToVertex)) - 2.0f*edgeDotVelocity*edgeDotBaseToVertex;

				c = edgeSquaredLength*(1.f - baseToVertex.lengthSquared()) + edgeDotBaseToVertex*edgeDotBaseToVertex;

				if (getLowestRoot(a, b, c, t, &newT))
				{
					float f = (edgeDotVelocity*newT - edgeDotBaseToVertex) / edgeSquaredLength;
					if (f >= 0.0f && f <= 1.0f)
					{
						t = newT;
						foundCollison = true;
						collisionPoint = p3 + f*edge;
					}
				}
			}

			// Set result:
			if (foundCollison == true)
			{
				// distance to collision: ’t’ is time of collision
				float distToCollision = t*colPackage->velocity.length();

				// Does this triangle qualify for the closest hit?
				// it does if it’s the first hit or the closest
				if (colPackage->foundCollision == false || distToCollision < colPackage->nearestDistance)
				{
					// Collision information nessesary for sliding
					colPackage->nearestDistance = distToCollision;
					colPackage->intersectionPoint = collisionPoint;
					colPackage->foundCollision = true;
					return true;
				}
			}

			
		} // if not backface

		return false;
	}

	// this is the fastest way to check whether the point is in the triangle or not
	// Keidy from Mr-Gamemaker
	bool ComponentsPool::checkPointInTriangle(const vec3f & point, const vec3f & pa, const vec3f & pb, const vec3f & pc)
	{
		vec3f e10 = pb - pa;
		vec3f e20 = pc - pa;
		float a = e10.dot(e10);
		float b = e10.dot(e20);
		float c = e20.dot(e20);
		float ac_bb = (a*c) - (b*b);
		vec3f vp(point.x - pa.x, point.y - pa.y, point.z - pa.z);
		float d = vp.dot(e10);
		float e = vp.dot(e20);
		float x = (d*c) - (e*b);
		float y = (e*a) - (d*b);
		float z = x + y - ac_bb;
		return ((in(z)& ~(in(x) | in(y))) & 0x80000000);
	}

	bool ComponentsPool::getLowestRoot(const float & a, const float & b, const float & c, const float & maxR, float * root)
	{
		// Check if a solution exists
		float determinant = b*b - 4.0f*a*c;

		// If determinant is negative it means no solutions.
		if (determinant < 0.0f)
		{
			return false;
		}

		// calculate the two roots: (if determinant == 0 then
		// x1==x2 but let’s disregard that slight optimization)
		float sqrtD = sqrt(determinant);
		float r1 = (-b - sqrtD) / (2 * a);
		float r2 = (-b + sqrtD) / (2 * a);

		// Sort so x1 <= x2
		if (r1 > r2)
		{
			float temp = r2;
			r2 = r1;
			r1 = temp;
		}
		// Get lowest root:
		if (r1 > 0 && r1 < maxR)
		{
			*root = r1;
			return true;
		}
		// It is possible that we want x2 - this can happen
		// if x1 < 0
		if (r2 > 0 && r2 < maxR)
		{
			*root = r2;
			return true;
		}
		// No (valid) solutions
		return false;
	}

	void ComponentsPool::destroyAllComponents(void)
	{
		if (transformComponents)
		{
			delete[]transformComponents;
			transformComponents = nullptr;
		}

		if (MeshRendererComponents)
		{
			delete[]MeshRendererComponents;
			MeshRendererComponents = nullptr;
		}

		if (dirlightComponents)
		{
			delete[]dirlightComponents;
			dirlightComponents = nullptr;
		}

		if (pointlightComponents)
		{
			delete[]pointlightComponents;
			pointlightComponents = nullptr;
		}

		if (scriptComponents)
		{
			delete[]scriptComponents;
			scriptComponents = nullptr;
		}

		if (guitextComponents)
		{
			delete[]guitextComponents;
			guitextComponents = nullptr;
		}

		if (spherecolliderComponents)
		{
			delete[]spherecolliderComponents;
			spherecolliderComponents = nullptr;
		}

		if (aabbComponents)
		{
			delete[]aabbComponents;
			aabbComponents = nullptr;
		}

		if (bulletComponents)
		{
			delete[]bulletComponents;
			bulletComponents = nullptr;
		}

		if (ellipsoidcolliderComponents)
		{
			delete[]ellipsoidcolliderComponents;
			ellipsoidcolliderComponents = nullptr;
		}

		if (meshcolliderComponents)
		{
			delete[]meshcolliderComponents;
			meshcolliderComponents = nullptr;
		}

		if (triggerComponents)
		{
			delete[]triggerComponents;
			triggerComponents = nullptr;
		}

		if (lineRendererComponents)
		{
			delete[]lineRendererComponents;
			lineRendererComponents = nullptr;
		}

		if (CanvasComponents)
		{
			delete[]CanvasComponents;
			CanvasComponents = nullptr;
		}

		if (dinoAIComponents)
		{
			delete[]dinoAIComponents;
			dinoAIComponents = nullptr;
		}


		ZERO_MEM(CSize);
	}
}
