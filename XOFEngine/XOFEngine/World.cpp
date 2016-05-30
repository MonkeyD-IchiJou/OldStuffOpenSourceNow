#include "World.h"

#include "EntitiesPool.h"
#include "ComponentsPool.h"

#include "componentsH_dclr.h"

#include "lua_backend.h"
#include "lua\lua.hpp"

#include "GLFW_Window.h"

#include "Entity.h"
#include "Collectable.h"
#include "FontsLibrary.h"

namespace pp
{
	lua_backend* World::luaHandle = nullptr;

	World::World(const string & file_path, const string &scenetag) :
		file_path(file_path), 
		scenetag(scenetag),
		allComponents(nullptr),
		allEntities(nullptr), 
		renderCam(nullptr),
		mainPlayer(nullptr),
		allCollectables(nullptr),
		S(nullptr)
	{
		if(luaHandle == nullptr) luaHandle = lua_backend::getInstance();
	}

	World::~World(void)
	{
		destroy();
	}

	bool World::create(void)
	{
		// prevent memory leak
		destroy();

		// first create the necessary entities
		allEntities = new EntitiesPool(scenetag);
		allEntities->create();

		// second is all the components pool
		allComponents = new ComponentsPool(scenetag);
		allComponents->create();

		// collectables create pls
		allCollectables = new Collectable();
		allCollectables->create();
		
		// then start to init all the entity 
		LUALoad();

		//allEntities->debug();

		/********************************************************/
		/*AT This Point of Time .. everything must be load well */
		/********************************************************/

		renderCam = ComponentsPool::cameraComponent;

		SphereColliderC::frustumHandle = renderCam->frustum;

		// need to let all the guis to know this man
 		allComponents->loadGUITex();

		// get the main dirlight
		dirlight = getDirLight();

		return true;
	}

	void World::update(const float & dt)
	{
		allComponents->updateAllComponents(dt);
		allCollectables->update(dt);

		dirlight = getDirLight();
		if (dirlight != nullptr)
		{
			// dir light special update for shadow frustum 
			dirlight->LightLookAtUpdate(dt, *renderCam);
		}
	}

	void World::updateALLCamAspect(const double & aspect)
	{
		allComponents->updateALLCamAspect(aspect);
	}

	void World::lateupdate(const float & dt)
	{
		allComponents->updatePrevMVP(renderCam->getView(), renderCam->getProjection());
		//allComponents->updateCameraComponents(dt);
		allCollectables->lateUpdate(dt);
	}

	DirLightC * World::getDirLight(void) const
	{
		return allComponents->getDirLight();
	}

	void World::renderMeshGPASS(void) const
	{
		allComponents->renderMesh();
	}

	void World::renderMeshDepthPASS(void) const
	{
		allComponents->renderMeshDepth();
	}

	void World::renderLightVolume(const bool & pon) const
	{
		allComponents->ReadPointLightsInfo(pon);
	}

	void World::renderAllText(void) const
	{
		allComponents->drawALLText();
	}

	void World::renderDebugMesh(void) const
	{
		allComponents->renderSphereCollider();
		allComponents->renderAABB();
		
	}

	void World::renderMeshColliders(void) const
	{
		allComponents->renderMeshCollider();
	}

	void World::renderEllipsoidColliders(void) const
	{
		allComponents->renderEllipsoidCollider();
	}

	void World::renderAllCollectable(void) const
	{
		allCollectables->draw();
	}

	void World::save(void)
	{
		allEntities->save(file_path);
	}

	ComponentsPool * World::getAllComponents(void)
	{
		return allComponents;
	}

	EntitiesPool * World::getAllEntities(void)
	{
		return this->allEntities;
	}

	void World::destroy(void)
	{
		if (allComponents)
		{
			allComponents->destroyAllComponents();
			allComponents = nullptr;
		}

		if (allEntities)
		{
			allEntities->destroyAllEntities();
			allEntities = nullptr;
		}

		if (allCollectables)
		{
			allCollectables->destroy();
			delete allCollectables;
			allCollectables = nullptr;
		}
	}

	void World::LUALoad(void)
	{
		// prevent memory leak
		if (S != nullptr)
		{
			lua_close(S);
		}

		// set up
		S = luaL_newstate();
		luaL_openlibs(S);

		// registration
		LUA_Registration();

		// execution 
		int i = luaL_dofile(S, file_path.c_str());
	}

	void World::LUA_Registration(void)
	{
		luaHandle->setCallBack(this);

		/* (in lua form) -- Entity = {

			New(int id, string name),

			addParent(),

			setActive(),

			addTag(),

			addMeshRenderer(),

			addDirLight(),

			addScript(),

			addCamera(),

			addPointLight(),

			addSphereCollider(),

			addAABBCollider(),

			shareAABBCollider(),

			addMeshCollider(),

			addEllipsoidCollider(),

			addTrigger(),

			TriggerLock(),

			addDinoAI(),

			getTransform = {
			setPosition(),
			setRotation(),
			setScale()
			},

			getCamera = {
			setPosition(),
			setTarget(),
			setUp(),
			setCamMode(),
			setMouseControl(),
			setLookingDir(),
			setMouseSentivity(),
			setZoomDistance(),
			setPitchLimit()
			}

			getMeshRenderer = {
			setColor,
			setEmissive,
			setShininess,
			setVisibility,
			setName
			},

			getDirLight = {
			setAmbient(),
			setDiffuse(),
			setSpecular(),
			setLightColor(),
			setLightDirection()
			}

			getScript = {
			setPath()
			}

			getSphereCollider = {
			setRadius(),
			addTag(),
			}

			getAABBCollider = {
			setHalfSize(),
			setPosition(),
			addTag()
			}

			getPointLight = {
			setDiffuse(),
			setSpecular(),
			setLightColor()
			}

			getMeshCollider = {
			setName(),
			}

			getEllipsoidCollider = {
			setRadius(vec3),
			}
		}
		*/

		// create a new empty table and push it onto the lua-c stack 
		lua_newtable(S);

		EntityRegister();
		AllComponentsRegister();
		TransformComponentRegister();
		MeshRendererComponentRegister();
		DirLightComponentRegister();
		PointLightComponentRegister();
		SphereColliderComponentRegister();
		AABBColliderComponentRegister();
		ScriptComponentRegister();
		MeshColliderComponentRegister();
		EllipsoidColliderComponentRegister();
		GUIComponentRegister();

		
		lua_setglobal(S, "Entity"); // after set global .. stacks return to 0

		lua_newtable(S);
		CameraComponentRegister();
		lua_setglobal(S, "Camera"); // after set global .. stacks return to 0
	}

	void World::GUIComponentRegister(void)
	{

		/*getGUIText = {
		setTextString(string),
		setTextColor(float, float, float, float),
		setTextMaterial(float, float, float, float, float, float, float, float, float),
		setFontType(string),
		setMaxLine(float)
		}*/


		lua_pushstring(S, "getGUIText");
		lua_newtable(S);

		lua_pushstring(S, "setTextString");
		luaHandle->pushLUA_setTextString(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setTextColor");
		luaHandle->pushLUA_setTextColor(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setTextMaterial");
		luaHandle->pushLUA_setTextMaterial(S);
		lua_settable(S, -3);


		lua_pushstring(S, "setFontType");
		luaHandle->pushLUA_setFontType(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setMaxLine");
		luaHandle->pushLUA_setMaxLine(S);
		lua_settable(S, -3);


		lua_settable(S, -3);
	}

	void World::EntityRegister(void)
	{
		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "New");
		luaHandle->pushLUA_CreateNewEntityCB(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "setActive");
		luaHandle->pushLUA_EntitySetActiveCB(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addTag");
		luaHandle->pushLUA_EntityAddTagCB(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addParent");
		luaHandle->pushLUA_EntityAddParentCB(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addCollectable");
		luaHandle->pushLUA_EntityAddCollectableCB(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void World::AllComponentsRegister(void)
	{
		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addMeshRenderer");
		luaHandle->pushLUA_AddMeshRendererComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addDirLight");
		luaHandle->pushLUA_AddDirLightComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addScript");
		luaHandle->pushLUA_AddScriptComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addCamera");
		luaHandle->pushLUA_AddCamComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addPointLight");
		luaHandle->pushLUA_AddPointLightComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addSphereCollider");
		luaHandle->pushLUA_AddSphereColliderComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addAABBCollider");
		luaHandle->pushLUA_AddAABBColliderComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addMeshCollider");
		luaHandle->pushLUA_AddMeshColliderComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addEllipsoidCollider");
		luaHandle->pushLUA_AddEllipsoidColliderComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
		
		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addTrigger");
		luaHandle->pushLUA_AddTriggerComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "TriggerLock");
		luaHandle->pushLUA_TriggerLock(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
		
		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addDinoAI");
		luaHandle->pushLUA_addDinoAIComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "shareDinoAI");
		luaHandle->pushLUA_shareDinoAIComponent(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addGUIText");
		luaHandle->pushLUA_addGUIText(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "addCanvas");
		luaHandle->pushLUA_addCanvas(S); // second value
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


	}

	void World::TransformComponentRegister(void)
	{
		/*getTransform = {
		setPosition(),
		setRotation(),
		setScale()
		},*/

		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getTransform");
		lua_newtable(S);

		lua_pushstring(S, "setPosition");
		luaHandle->pushLUA_setPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setRotation");
		luaHandle->pushLUA_setRotationCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setScale");
		luaHandle->pushLUA_setScaleCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void World::MeshRendererComponentRegister(void)
	{
		/*getMeshRenderer = {
			setColor,
			setEmissive,
			setShininess,
			setVisibility,
			setName
		},*/

		// multidimensional table
		lua_pushstring(S, "getMeshRenderer");
		lua_newtable(S);

		lua_pushstring(S, "setName");
		luaHandle->pushLUA_SetMeshNameCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setColor");
		luaHandle->pushLUA_SetColorCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setShininess");
		luaHandle->pushLUA_SetShininessCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setEmissive");
		luaHandle->pushLUA_SetEmissiveCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setVisibility");
		luaHandle->pushLUA_SetObjectVisibilityCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);

	}

	void World::CameraComponentRegister(void)
	{
		/*Camera = {
			setPosition(),
			setTarget(),
			setUp(),
			setCamMode(),
			setMouseControl(),
			setLookingDir(),
			setMouseSentivity(),
			setZoomDistance(),
			setPitchLimit()
		}*/

		lua_pushstring(S, "setPosition");
		luaHandle->pushLUA_SetCamPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setTarget");
		luaHandle->pushLUA_SetCamTargetCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setUp");
		luaHandle->pushLUA_SetCamUpCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setCamMode");
		luaHandle->pushLUA_SetCamModeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setMouseControl");
		luaHandle->pushLUA_SetMouseControlCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setLookingDir");
		luaHandle->pushLUA_SetLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setMouseSentivity");
		luaHandle->pushLUA_SetMouseSensitivityCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setZoomDistance");
		luaHandle->pushLUA_SetZoomDistanceCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setPitchLimit");
		luaHandle->pushLUA_SetPitchLimitCB(S);
		lua_settable(S, -3);
	}

	void World::ScriptComponentRegister(void)
	{
		lua_pushstring(S, "getScript");
		lua_newtable(S);

		lua_pushstring(S, "setPath");
		luaHandle->pushLUA_setScriptPath(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
	}

	void World::DirLightComponentRegister(void)
	{
		/*getDirLight = {
			setAmbient(),
			setDiffuse(),
			setSpecular(),
			setLightColor(),
			setLightDirection()
		}*/

		// multidimensional table
		lua_pushstring(S, "getDirLight");
		lua_newtable(S);

		lua_pushstring(S, "setAmbient");
		luaHandle->pushLUA_SetAmbientCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setDiffuse");
		luaHandle->pushLUA_SetDiffuseCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setSpecular");
		luaHandle->pushLUA_SetSpecularCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setLightColor");
		luaHandle->pushLUA_SetLightColorCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setLightDirection");
		luaHandle->pushLUA_SetLightDirectionCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
	}

	void World::PointLightComponentRegister(void)
	{
		/*getPointLight = {
			setDiffuse(),
			setSpecular(),
			setLightColor()
		}*/

		lua_pushstring(S, "getPointLight");
		lua_newtable(S);

		lua_pushstring(S, "setDiffuse");
		luaHandle->pushLUA_PointLightSetDiffuseCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setSpecular");
		luaHandle->pushLUA_PointLightSetSpecularCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setLightColor");
		luaHandle->pushLUA_PointLightSetLightColorCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
	}

	void World::SphereColliderComponentRegister(void)
	{
		/*getSphereCollider = {
			setRadius()
		}*/

		lua_pushstring(S, "getSphereCollider");
		lua_newtable(S);

		lua_pushstring(S, "setRadius");
		luaHandle->pushLUA_setfradiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "addTag");
		luaHandle->pushLUA_SphereCollideAddTagCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
	}

	void World::AABBColliderComponentRegister(void)
	{
		/*getAABBCollider = {
			setHalfSize(),
			setPosition()
		}*/

		lua_pushstring(S, "getAABBCollider");
		lua_newtable(S);

		lua_pushstring(S, "setHalfSize");
		luaHandle->pushLUA_setHalfSizeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setPosition");
		luaHandle->pushLUA_setPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "addTag");
		luaHandle->pushLUA_AABBCollideAddTagCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
	}

	void World::MeshColliderComponentRegister(void)
	{
		/*getMeshCollider = {
		setName(),
		}*/

		lua_pushstring(S, "getMeshCollider");
		lua_newtable(S);

		lua_pushstring(S, "setName");
		luaHandle->pushLUA_setMeshColliderNameCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
	}

	void World::EllipsoidColliderComponentRegister(void)
	{
		/*getEllipsoidCollider = {
			setRadius(vec3),
		}*/

		lua_pushstring(S, "getEllipsoidCollider");
		lua_newtable(S);

		lua_pushstring(S, "setRadius");
		luaHandle->pushLUA_setEllipsoidRadiusCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);

	}

	/***********************************************************************/
	/***********************************************************************/
	/* ALL lua callback functions below ************************************/
	/***********************************************************************/
	/***********************************************************************/

	int World::LUA_CreateNewEntityCB(lua_State * L)
	{
		Entity* entity = allEntities->FetchEntity();
		entity->setGUID((int)lua_tointeger(S, 1));
		entity->setEntityName(lua_tostring(S, 2));

		entity->transformC = allComponents->FetchTransformC();
		entity->AddComponent(entity->transformC);

		return 0;
	}
	int World::LUA_EntityAddParentCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		Entity* parent = allEntities->findEntity((int)lua_tointeger(S, 2));

		entity->setParent(parent);
		parent->setChild(entity);

		return 0;
	}
	int World::LUA_EntitySetActiveCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		bool i = itob(lua_toboolean(L, 2));
		entity->setActive(i);

		return 0;
	}
	int World::LUA_EntityAddTagCB(lua_State * L)
	{

		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->setTag(lua_tostring(L, 2));

		return 0;
	}
	int World::LUA_EntityAddCollectableCB(lua_State * L)
	{
		allCollectables->add(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)));
		return 0;
	}
	int World::LUA_setPositionCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->transformC->position.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));
		entity->transformC->localPosition = entity->transformC->position;
		return 0;
	}
	int World::LUA_setRotationCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->transformC->rotation.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));
		return 0;
	}
	int World::LUA_setScaleCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->transformC->scale.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));
		return 0;
	}
	int World::LUA_SetCamPositionCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->position.Set((float)lua_tonumber(S, 1), (float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3));

		return 0;
	}
	int World::LUA_SetCamTargetCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->target.Set((float)lua_tonumber(S, 1), (float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3));

		return 0;
	}
	int World::LUA_SetCamUpCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->up.Set((float)lua_tonumber(S, 1), (float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3));

		return 0;
	}
	int World::LUA_SetCamModeCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->mode = (CAMERA_MODE)lua_tointeger(S, 1);

		return 0;
	}
	int World::LUA_SetMouseControlCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->mouseControl = itob(lua_toboolean(S, 1));

		return 0;
	}
	int World::LUA_SetLookingDirCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->lookingDir.Set((float)lua_tonumber(S, 1), (float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3));

		vec3f A = ComponentsPool::cameraComponent->lookingDir;
		vec3f B = A;
		B.y = 0.f;

		float dotProduct = A.dot(B);
		float MULTAB = A.length() * B.length();

		ComponentsPool::cameraComponent->setTiltingAngle(RadianToDegree( acos(dotProduct / MULTAB)));

		return 0;
	}
	int World::LUA_SetMouseSensitivityCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->MOUSE_SENSITIVITY = (float)lua_tonumber(S, 1);

		return 0;
	}
	int World::LUA_SetZoomDistanceCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->ZOOM_DISTANCE = (float)lua_tonumber(S, 1);

		return 0;
	}
	int World::LUA_SetPitchLimitCB(lua_State * L)
	{
		ComponentsPool::cameraComponent->PITCH_LIMIT = (float)lua_tonumber(S, 1);

		return 0;
	}
	int World::LUA_AddMeshRendererComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->AddComponent(allComponents->FetchMeshRendererC());



		return 0;
	}
	int World::LUA_SetColorCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<MeshRendererC>()->color.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));

		return 0;
	}
	int World::LUA_SetEmissiveCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<MeshRendererC>()->emissive = (float)lua_tonumber(S, 2);

		return 0;
	}
	int World::LUA_SetShininessCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<MeshRendererC>()->shininess = (float)lua_tonumber(S, 2);

		return 0;
	}
	int World::LUA_SetObjectVisibilityCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<MeshRendererC>()->enabled = itob(lua_toboolean(S, 2));

		return 0;
	}
	int World::LUA_SetMeshNameCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<MeshRendererC>()->meshName = lua_tostring(S, 2);

		return 0;
	}
	int World::LUA_AddDirLightComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->AddComponent(allComponents->FetchDirlightC());

		return 0;
	}
	int World::LUA_SetLightColorCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<DirLightC>()->lightColor.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));
		return 0;
	}
	int World::LUA_SetAmbientCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<DirLightC>()->ambient.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));

		return 0;
	}
	int World::LUA_SetDiffuseCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<DirLightC>()->diffuse.Set((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4));
		return 0;
	}
	int World::LUA_SetSpecularCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<DirLightC>()->specular.Set((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4));
		return 0;
	}
	int World::LUA_SetLightDirectionCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<DirLightC>()->lightdirection.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));
		return 0;
	}
	int World::LUA_AddScriptComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->AddComponent(allComponents->FetchScriptC());

		return 0;
	}
	int World::LUA_setScriptPath(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));

		for (auto x : entity->findAllComponentT<ScriptC>())
		{
			// if it is a default file
			if (x->file_path == "Content//scripts//default.lua")
			{
				x->file_path = lua_tostring(S, 2);
				break;
			}
		}

		return 0;
	}
	int World::LUA_AddPointLightComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->AddComponent(allComponents->FetchPointlightC());

		return 0;
	}
	int World::LUA_PointLightSetLightColorCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<PointLightC>()->lightColor.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));

		return 0;
	}
	int World::LUA_PointLightSetDiffuseCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<PointLightC>()->diffuse.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));

		return 0;
	}
	int World::LUA_PointLightSetSpecularCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<PointLightC>()->specular.Set((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4));

		return 0;
	}
	int World::LUA_AddSphereColliderComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->AddComponent(allComponents->FetchSphereColliderC());

		return 0;
	}
	int World::LUA_setfradiusCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<SphereColliderC>()->setfradius((float)lua_tonumber(S, 2));

		return 0;
	}
	int World::LUA_SphereCollideAddTagCB(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<SphereColliderC>()->setTag(lua_tostring(S, 2));

		return 0;
	}
	int World::LUA_AddEllipsoidColliderComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->AddComponent(allComponents->FetchEllipsoidColliderC());

		return 0;
	}
	int World::LUA_setEllipsoidRadiusCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<EllipsoidColliderC>()->eRadius.Set((float)lua_tonumber(S, 2), (float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4));

		return 0;
	}
	int World::LUA_AddAABBColliderComponent(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		int aabbid = (int)lua_tointeger(S, 2);
		AABB* aabb = allComponents->FetchAABBC();

		aabb->guid = aabbid; // every aabb is unique in its own entity
		entity->AddComponent(aabb);

		return 0;
	}
	int World::LUA_setPosCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		int aabbid = (int)lua_tointeger(L, 2);

		std::vector <AABB*> allaabb = entity->findAllComponentT<AABB>();
		AABB* chosenOne = nullptr;

		for (auto&x : allaabb)
		{
			if (x->guid == aabbid)
			{
				chosenOne = x;
				break;
			}
		}

		if (chosenOne)
			chosenOne->setPos(vec3f((float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4), (float)lua_tonumber(S, 5)));

		return 0;
	}
	int World::LUA_setHalfSizeCB(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		int aabbid = (int)lua_tointeger(S, 2);

		std::vector <AABB*> allaabb = entity->findAllComponentT<AABB>();
		AABB* chosenOne = nullptr;

		for (auto&x : allaabb)
		{
			if (x->guid == aabbid)
			{
				chosenOne = x;
				break;
			}
		}

		if (chosenOne)
			chosenOne->setHalfSize(vec3f((float)lua_tonumber(S, 3), (float)lua_tonumber(S, 4), (float)lua_tonumber(S, 5)));

		return 0;
	}
	int World::LUA_AABBCollideAddTagCB(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		int aabbid = (int)lua_tointeger(L, 2);

		std::vector <AABB*> allaabb = entity->findAllComponentT<AABB>();
		AABB* chosenOne = nullptr;

		for (auto&x : allaabb)
		{
			if (x->guid == aabbid)
			{
				chosenOne = x;
				break;
			}
		}

		if (chosenOne)
			chosenOne->setTag(lua_tostring(S, 3));

		return 0;
	}
	int World::LUA_AddMeshColliderComponent(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		MeshColliderC* m = allComponents->FetchMeshColliderC();
		entity->AddComponent(m);

		MeshRendererC* r = entity->findComponentT<MeshRendererC>();

		if (r)
			m->setMeshName(r->meshName);

		return 0;
	}
	int World::LUA_setMeshColliderNameCB(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		entity->findComponentT<MeshColliderC>()->setMeshName(lua_tostring(S, 2));

		return 0;
	}

	int World::LUA_AddTriggerComponent(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->AddComponent(allComponents->FetchTriggerC());

		return 0;
	}


	int World::LUA_TriggerLock(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(S, 1));
		Entity* entity2 = allEntities->findEntity((int)lua_tointeger(S, 2));

		// will share the same triggerC
		entity->pureAddComponent(entity2->findComponentT<TriggerC>());
		bool add = false;
		entity2->findComponentT<TriggerC>()->alerts.push_back(add);
		return 0;
	}

	int World::LUA_addDinoAIComponent(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->AddComponent(allComponents->FetchDinoAIC());
		return 0;
	}

	int World::LUA_shareDinoAIComponent(lua_State* L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		Entity* entity2 = allEntities->findEntity((int)lua_tointeger(L, 2));
		int whichone = (int)lua_tointeger(L, 3);


		DinoAIC* a = entity2->findComponentT<DinoAIC>();

		if (whichone == 0)
		{
			a->HeadPosition = &entity->transformC->position;
			a->BodyPosition = &entity2->transformC->position;
		}
		
		else if (whichone == 1)
		{
			a->Tail[(int)lua_tointeger(L, 4)].TailT = entity->transformC;
		}

		else
		{

		}

		// will share the same triggerC
		entity->pureAddComponent(a);

		return 0;
	}

	int World::LUA_addGUIText(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->AddComponent(allComponents->FetchGUITextC());
		
		return 0;
	}

	int World::LUA_setTextString(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<GUIText>()->setTextString(lua_tostring(L, 2));
		return 0;
	}

	int World::LUA_setTextColor(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<GUIText>()->setColor((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4));
		entity->findComponentT<GUIText>()->setAlpha((float)lua_tonumber(L, 5));
		return 0;
	}

	int World::LUA_setTextMaterial(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		FontMaterial& m = entity->findComponentT<GUIText>()->material;
		m.width = (float)lua_tonumber(L, 2);
		m.edge = (float)lua_tonumber(L, 3);
		m.borderwidth = (float)lua_tonumber(L, 4);
		m.borderedge = (float)lua_tonumber(L, 5);
		m.offsetx = (float)lua_tonumber(L, 6);
		m.offsety = (float)lua_tonumber(L, 7);
		m.coloroutline.Set((float)lua_tonumber(L, 8), (float)lua_tonumber(L, 9), (float)lua_tonumber(L, 10));
		return 0;
	}

	int World::LUA_setFontType(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<GUIText>()->setFontType(FontsLibrary::getInstance()->FontTypes[lua_tostring(L, 2)]);
		return 0;
	}

	int World::LUA_setMaxLine(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->findComponentT<GUIText>()->setMaxLineSize((float)lua_tonumber(L, 2));
		return 0;
	}

	int World::LUA_addCanvas(lua_State * L)
	{
		Entity* entity = allEntities->findEntity((int)lua_tointeger(L, 1));
		entity->AddComponent(allComponents->FetchCanvas());
		return 0;
	}
}
