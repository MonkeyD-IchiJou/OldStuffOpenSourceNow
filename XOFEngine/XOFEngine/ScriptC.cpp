#include "ScriptC.h"
#include "lua_backend.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "lua\lua.hpp"

#include "Entity.h"
#include "CameraC.h"
#include "TransformationC.h"
#include "MeshRendererC.h"
#include "TriggerC.h"
#include "DirLightC.h"
#include "SphereColliderC.h"
#include "AABB.h"
#include "EllipsoidColliderC.h"
#include "LineRendererC.h"
#include "DinoAIC.h"
#include "Canvas.h"

#include "GUIText.h"

#include "ComponentsPool.h" 
#include "EntitiesPool.h"
#include "PlayerManager.h"

#include "SceneManager.h"
#include "scenebase.h"
#include "World.h"
#include "GraphicEngine.h"
#include "FontsLibrary.h"
#include "GUIText.h"

#include "GraphicScale.h"

#include "GLFW_Window.h"

namespace pp
{

	lua_backend* ScriptC::luaHandle = nullptr;
	Keyboard* ScriptC::keyboardHandle = nullptr;
	Mouse* ScriptC::mouseHandle = nullptr;
	SceneManager* ScriptC::sceneHandle = nullptr;
	GraphicEngine* ScriptC::gHandle = nullptr;
	PlayerManager* ScriptC::playerHandle = nullptr;

	ScriptC::ScriptC(void) :
		Component(SCRIPT),
		S(nullptr),
		file_path("Content//scripts//default.lua"),
		camHandle(nullptr),
		transformHandle(nullptr),
		rendererHandle(nullptr),
		dirlightHandle(nullptr),
		lightHandle(nullptr),
		pickerHandle(nullptr),
		spherecolliderHandle(nullptr),
		activeRun(true),
		ellipsoidHandle(nullptr),
		componentsDaddy(nullptr),
		linerendererhandle(nullptr),
		dinoAIHandle(nullptr),
		guiHandle(nullptr),
		canvasHandle(nullptr)
	{
		if (luaHandle == nullptr) luaHandle = lua_backend::getInstance();
		if (keyboardHandle == nullptr) keyboardHandle = Keyboard::getInstance();
		if (mouseHandle == nullptr) mouseHandle = Mouse::getInstance();
		if (playerHandle == nullptr) playerHandle = PlayerManager::getInstance();
		if (sceneHandle == nullptr) sceneHandle = SceneManager::getInstance();
		if (gHandle == nullptr) gHandle = GraphicEngine::getInstance();
	}

	ScriptC::~ScriptC(void)
	{
		if (S != nullptr)
		{
			lua_close(S);
		}
	}

	void ScriptC::update(const float& dt)
	{
		if (updatedFlag)
		{
			// prevent memory leak
			if (S != nullptr)
			{
				lua_close(S);
				S = nullptr;
			}

			if (S == nullptr)
			{
				// component handles update first
				transformHandle = getOwner()->transformC;
				camHandle = ComponentsPool::cameraComponent;
				rendererHandle = getOwner()->findComponentT<MeshRendererC>();
				lightHandle = getOwner()->findComponentT<LightC>();
				dirlightHandle = getOwner()->findComponentT<DirLightC>();
				spherecolliderHandle = getOwner()->findComponentT<SphereColliderC>();
				aabbHandles = getOwner()->findAllComponentT<AABB>();
				ellipsoidHandle = getOwner()->findComponentT<EllipsoidColliderC>();
				triggerhandle = getOwner()->findComponentT<TriggerC>();
				linerendererhandle = getOwner()->findComponentT<LineRendererC>();
				dinoAIHandle = getOwner()->findComponentT<DinoAIC>();
				componentsDaddy = SceneManager::activeScene->getWorld()->getAllComponents();
				guiHandle = getOwner()->findComponentT<GUIText>();
				canvasHandle = getOwner()->findComponentT<CanvasC>();

				if (getOwner()->getParent() != nullptr)
				{
					dinoAIHandle = getOwner()->getParent()->findComponentT<DinoAIC>();
					canvasHandle = getOwner()->getParent()->findComponentT<CanvasC>();
				}

				for (auto &x : getOwner()->children)
				{
					if (x->isTag("GUINAME"))
					{
						GUIName = x;
						break;
					}
				}

				// set up
				S = luaL_newstate();
				luaL_openlibs(S);

				// registration
				registration();

				// execution 
				luaL_dofile(S, file_path.c_str());

				lua_getglobal(S, "Init");

				// after this pcall .. above stack will be remove 
				if (lua_pcall(S, 0, 0, 0) != EXIT_SUCCESS) // 1 arguments, 0 return
				{
 					printf("error running function printMsg \n");
					lua_close(S);
					S = nullptr;
				}
			}

			updatedFlag = false;
		}


		// run the update function in the script
		if (S != nullptr && getOwner()->isActive() && activeRun) run(dt);
	}

	void ScriptC::run(const float &dt)
	{
		// need to tell the callback is this baby
		luaHandle->setCallBack(this);

		lua_getglobal(S, "Update");
		lua_pushnumber(S, dt); // push the delta time

		// after this pcall .. above stack will be remove 
		if (lua_pcall(S, 1, 0, 0) != EXIT_SUCCESS) // 1 arguments, 0 return
		{
			printf("error running function printMsg \n");
			lua_close(S);
		}
	}

	void ScriptC::registration(void)
	{
		// tell the lua backend that, we are going to execute this script
		// then lua backend will call our callback functions
		luaHandle->setCallBack(this);

		// (in lua form) 
		/*
		OWN = {
			getTransform = {
				Translate(vec3)
				Rotate(vec3)
				RotateAround(vec3 , vec3, float)
				Scale(vec3)
				setPosition(vec3)
				getPosition()
				setRotation(vec3)
				getRotation()
				setScale(vec3)
				getScale()
				setLocalPosition(vec3)
				getLocalPosition()
				setLocalRotate(vec3)
				getLocalRotate()
				setLocalScale(vec3)
				getLocalScale()
				setLookAt(vec3)
				getLookAt()
			},

			getRenderer = {
				setColor(vec3),
				setEmissive(float),
				setShininess(float),
				setEnableVisible(bool),
				setMeshName(string),
				getColor(),
				getEmissive(),
				getShininess(),
				getEnableVisible(),
				getMeshName()
			},

			getCamera = {
				
				// Set functions //

				setCamPosition(vec3)
				setCamTarget(vec3)
				setCamUp(vec3)
				setCamMode(int)
				setMouseControl(bool)
				setLookingDir(vec3)
				setMouseSensitivity(float)
				setZoomDistance(float)
				setZoomSpeed(float)
				setPitchLimit(float)
				setFOVY(double)
				setZNear(double)
				setZFar(double)

				// Get functions //

				getCamPosition(vec3)
				getCamTarget(vec3)
				getCamUp(vec3)
				getCamMode(int)
				getMouseControl(bool)
				getLookingDir(vec3)
				getMouseSensitivity(float)
				getZoomDistance(float)
				getZoomSpeed(float)
				getPitchLimit(float)
				getFOVY(double)
				getZNear(double)
				getZFar(double)
				
			},

			getDirLight = {
				setLightDirection(vec3),
				getLightDirection(),
				changeLightDirection(vec3, float),
			},
			getLight = {
				setLightPos(vec3),
				setLightColor(vec3),
				setAmbient(vec3),
				setDiffuse(vec3),
				setSpecular(vec3),
				getLightPos(),
				getLightColor(),
				getAmbient(),
				getDiffuse(),
				getSpecular()
			},

			getSphere = {

			setRadius(vec3)
			getRadius()
			setCollide(vec3)
			isCollide()
			},

			getAABB = {

			setPos(int, vec3)
			setHalfSize(int, vec3)
			getMin(int)
			getMax(int)
			setCollide(int, vec3)
			isCollide(int)
			getRPos(int)
			collideInfo(int)
			checkCollide(int, string)
			}

			getEllipsoidCollider = {

			setR3Gravity(vec3),
			getR3Gravity(),
			setR3Vel(vec3),
			getR3Vel(),
			setERadius(vec3),
			getERadius(),
			isCollide(bool gravityornot),
			CollisionCheck(dt)

			}

			getTrigger = {
			 isTrigger(),
			 setTrigger()
			}

		}

		*/

		// create a new empty table and push it onto the lua-c stack 
		lua_newtable(S);

		TransformComponentRegister();
		if(rendererHandle) MeshRendererComponentRegister();
		if (dirlightHandle) DirLightComponentRegister();
		if (lightHandle) LightComponentRegister();
		if (spherecolliderHandle) SphereColliderComponentRegister();
		if (aabbHandles.size() > 0) AABBColliderComponentRegister();
		if (ellipsoidHandle) EllipsoidColliderComponentRegister();
		if (triggerhandle) TriggerComponentRegister();
		if (linerendererhandle) LineRendererComponenetRegister();
		if (dinoAIHandle) DinoAIComponentRegister();
		if (guiHandle) GUIComponentRegister();
		if (canvasHandle) CanvasComponentRegister();

		lua_setglobal(S, "OWN"); // after set global .. stacks return to 0

		// input got its own input shit
		InputRegister();

		SceneRegister();

		PlayerRegister();

		GraphicsSettingRegister();

		if (camHandle)
		{
			lua_newtable(S);
			CameraComponentRegister();
			lua_setglobal(S, "Camera"); // after set global .. stacks return to 0
		}
	}
	
	void ScriptC::InputRegister()
	{
		/* (in lua form) --
		Input = {
		isKeyPressed(KEY), 
		isKeyHold(KEY), 
		isKeyTouched(KEY), 
		isMouseClick(), 
		isMouseHold(), 
		getScrolling() 
		}*/

		// create a new empty table and push it onto the lua-c stack 
		lua_newtable(S);

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "isMouseClick");
		luaHandle->pushLUA_isMouseClickCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "isMouseHold");
		luaHandle->pushLUA_isMouseHoldCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "getScrolling");
		luaHandle->pushLUA_getScrollingCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "isKeyPressed");
		luaHandle->pushLUA_isKeyPressedCB(S); // second value


		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "isKeyHold");
		luaHandle->pushLUA_isKeyHoldCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------



		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "isKeyTouched");
		luaHandle->pushLUA_isKeyTouchedCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "CursorEnable");
		luaHandle->pushLUA_setCursorEnableCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "CursorPosition");
		luaHandle->pushLUA_getCursorPositionCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "CursorVsGUIAABB");
		luaHandle->pushLUA_CursorVsGUIAABBCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		lua_setglobal(S, "Input"); // after set global .. stacks return to 0
	}

	void ScriptC::TransformComponentRegister(void)
	{
		/*OWN = {
			getTransform = {
				Translate(vec3)
				Rotate(vec3)
				RotateAround(vec3 , vec3, float)
				Scale(vec3)
				setPosition(vec3)
				getPosition()
				setRotation(vec3)
				getRotation()
				setScale(vec3)
				getScale()
				setLocalPosition(vec3)
				getLocalPosition()
				setLocalRotate(vec3)
				getLocalRotate()
				setLocalScale(vec3)
				getLocalScale()
				LookAt(vec3, bool)
			},
		},*/

		// Transform Component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getTransform");
		lua_newtable(S);

			lua_pushstring(S, "Translate");
			luaHandle->pushLUA_TranslateCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "Rotate"); 
			luaHandle->pushLUA_RotateCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "RotateAround");
			luaHandle->pushLUA_RotateAroundCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "Scale");
			luaHandle->pushLUA_ScaleCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setPosition");
			luaHandle->pushLUA_setPositionCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getPosition");
			luaHandle->pushLUA_getPositionCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setRotation");
			luaHandle->pushLUA_setRotationCB(S);
			lua_settable(S, -3);
			
			lua_pushstring(S, "getRotation");
			luaHandle->pushLUA_getRotationCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setScale");
			luaHandle->pushLUA_setScaleCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getScale");
			luaHandle->pushLUA_getScaleCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLocalPosition");
			luaHandle->pushLUA_setLocalPositionCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLocalPosition");
			luaHandle->pushLUA_getLocalPositionCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLocalRotation");
			luaHandle->pushLUA_setLocalRotationCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLocalRotation");
			luaHandle->pushLUA_getLocalRotationCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLocalScale");
			luaHandle->pushLUA_getLocalScaleCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLocalScale");
			luaHandle->pushLUA_getLocalScaleCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "LookAt");
			luaHandle->pushLUA_LookAtCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "pushLookAt");
			luaHandle->pushLUA_pushLookAtCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "pushRotate");
			luaHandle->pushLUA_pushRotateCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setDragonRotate");
			luaHandle->pushLUA_setSDragRotateCB(S);
			lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::MeshRendererComponentRegister(void)
	{
		// RENDERER component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getRenderer");
		lua_newtable(S);

			lua_pushstring(S, "setColor");
			luaHandle->pushLUA_SetColorCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setEmissive");
			luaHandle->pushLUA_SetEmissiveCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setShininess");
			luaHandle->pushLUA_SetShininessCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setEnableVisible");
			luaHandle->pushLUA_SetObjectVisibilityCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setMeshName");
			luaHandle->pushLUA_SetMeshNameCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getColor");
			luaHandle->pushLUA_GetColorCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getEmissive");
			luaHandle->pushLUA_GetEmissiveCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getShininess");
			luaHandle->pushLUA_GetShininessCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getEnableVisible");
			luaHandle->pushLUA_GetObjectVisibilityCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getMeshName");
			luaHandle->pushLUA_GetMeshNameCB(S);
			lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::CameraComponentRegister(void)
	{
		// CAMERA component
		//----------------------------------------------------------------------------------------

		// Set functions //
		lua_pushstring(S, "setCamPosition");
		luaHandle->pushLUA_SetCamPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setCamTarget");
		luaHandle->pushLUA_SetCamTargetCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setCamUp");
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

		lua_pushstring(S, "setMouseSensitivity");
		luaHandle->pushLUA_SetMouseSensitivityCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setZoomDistance");
		luaHandle->pushLUA_SetZoomDistanceCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setZoomSpeed");
		luaHandle->pushLUA_SetZoomSpeedCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setPitchLimit");
		luaHandle->pushLUA_SetPitchLimitCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setFOVY");
		luaHandle->pushLUA_SetFOVYCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setZNear");
		luaHandle->pushLUA_SetZNearCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setZFar");
		luaHandle->pushLUA_SetZFarCB(S);
		lua_settable(S, -3);

		// Get fucntions // 
		lua_pushstring(S, "getCamPosition");
		luaHandle->pushLUA_GetCamPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getCamTarget");
		luaHandle->pushLUA_GetCamTargetCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getCamUp");
		luaHandle->pushLUA_GetCamUpCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getCamMode");
		luaHandle->pushLUA_GetCamModeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getMouseControl");
		luaHandle->pushLUA_GetMouseControlCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getLookingDir");
		luaHandle->pushLUA_GetLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getMouseSensitivity");
		luaHandle->pushLUA_GetMouseSensitivityCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getZoomDistance");
		luaHandle->pushLUA_GetZoomDistanceCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getZoomSpeed");
		luaHandle->pushLUA_GetZoomSpeedCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getPitchLimit");
		luaHandle->pushLUA_GetPitchLimitCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getFOVY");
		luaHandle->pushLUA_GetFOVYCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getZNear");
		luaHandle->pushLUA_GetZNearCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getZFar");
		luaHandle->pushLUA_GetZFarCB(S);
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::DirLightComponentRegister(void)
	{
		// LIGHT component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getDirLight");
		lua_newtable(S);
			
			lua_pushstring(S, "setLightDirection");
			luaHandle->pushLUA_SetLightDirectionCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLightDirection");
			luaHandle->pushLUA_GetLightDirectionCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "changeLightDirection");
			luaHandle->pushLUA_ChangeLightDirectionCB(S);
			lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::LightComponentRegister(void)
	{
		// LIGHT component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getLight");
		lua_newtable(S);
			
			lua_pushstring(S, "setLightPos");
			luaHandle->pushLUA_SetLightPosCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLightColor");
			luaHandle->pushLUA_SetLightColorCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLightAmbient");
			luaHandle->pushLUA_SetAmbientCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLightDiffuse");
			luaHandle->pushLUA_SetDiffuseCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "setLightSpecular");
			luaHandle->pushLUA_SetSpecularCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLightPos");
			luaHandle->pushLUA_GetLightPosCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLightColor");
			luaHandle->pushLUA_GetLightColorCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLightAmbient");
			luaHandle->pushLUA_GetAmbientCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLightDiffuse");
			luaHandle->pushLUA_GetDiffuseCB(S);
			lua_settable(S, -3);

			lua_pushstring(S, "getLightSpecular");
			luaHandle->pushLUA_GetSpecularCB(S);
			lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::SphereColliderComponentRegister(void)
	{
		// Sphere collider component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getSphere");
		lua_newtable(S);

		lua_pushstring(S, "setRadius");
		luaHandle->pushLUA_setfradiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getRadius");
		luaHandle->pushLUA_getfradiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setCollide");
		luaHandle->pushLUA_setSphereCollideCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "isCollide");
		luaHandle->pushLUA_isSphereCollideCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::EllipsoidColliderComponentRegister(void)
	{
		/*getEllipsoidCollider = {

			setR3Gravity(vec3),
			getR3Gravity(),
			setR3Vel(vec3),
			getR3Vel(),
			setERadius(vec3),
			getERadius(),
			isCollide(bool gravityornot),
			CollisionCheck(dt)
		}*/
		
		// ellipsoidcollider component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getEllipsoidCollider");
		lua_newtable(S);

		lua_pushstring(S, "setR3Vel");
		luaHandle->pushLUA_setEllipsoidR3VelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getR3Vel");
		luaHandle->pushLUA_getEllipsoidR3VelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setERadius");
		luaHandle->pushLUA_setEllipsoidRadiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getERadius");
		luaHandle->pushLUA_getEllipsoidRadiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setR3Gravity");
		luaHandle->pushLUA_setEllipsoidR3GravityCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getR3Gravity");
		luaHandle->pushLUA_getEllipsoidR3GravityCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "isCollide");
		luaHandle->pushLUA_isEllipsoidCollideCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "CollisionCheck");
		luaHandle->pushLUA_EllipsoidCollisionCheckCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::AABBColliderComponentRegister(void)
	{
		// Sphere collider component
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "getAABB");
		lua_newtable(S);

		lua_pushstring(S, "setPos");
		luaHandle->pushLUA_setPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setHalfSize");
		luaHandle->pushLUA_setHalfSizeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getMin");
		luaHandle->pushLUA_getMinCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getMax");
		luaHandle->pushLUA_getMaxCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getRPos");
		luaHandle->pushLUA_getRPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setCollide");
		luaHandle->pushLUA_isAABBCollideCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "isCollide");
		luaHandle->pushLUA_isAABBCollideCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "checkCollide");
		luaHandle->pushLUA_checkAABBCollideCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "collideInfo");
		luaHandle->pushLUA_getAABBCollideInfoCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::TriggerComponentRegister(void)
	{
		/*getTrigger = {
			 isTrigger(),
			 setTrigger()
		}*/
		lua_pushstring(S, "getTrigger");
		lua_newtable(S);

		lua_pushstring(S, "isTrigger");
		luaHandle->pushLUA_isTriggerCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setTrigger");
		luaHandle->pushLUA_setTriggerCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

	}

	void ScriptC::LineRendererComponenetRegister(void)
	{
		/*getLineRenderer = {
		StartLine(),
		EndLine()
		}*/
		lua_pushstring(S, "getLineRenderer");
		lua_newtable(S);

		lua_pushstring(S, "StartLine");
		luaHandle->pushLUA_StartLineCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "EndLine");
		luaHandle->pushLUA_EndLineCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::DinoAIComponentRegister(void)
	{
		/*getDinoAI = {
		setDinoHeadLookingDir(),
		setDinoBodyLookingDir(),
		setDinoTailLookingDir(),
		getDinoHeadLookingDir,
		getDinoBodyLookingDir,
		getDinoTailLookingDir,
		}*/
		lua_pushstring(S, "getDinoAI");
		lua_newtable(S);

		lua_pushstring(S, "setDinoHeadLookingDir");
		luaHandle->pushLUA_setDinoHeadLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setDinoBodyLookingDir");
		luaHandle->pushLUA_setDinoBodyLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setDinoTailLookingDir");
		luaHandle->pushLUA_setDinoTailLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getDinoHeadLookingDir");
		luaHandle->pushLUA_getDinoHeadLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getDinoBodyLookingDir");
		luaHandle->pushLUA_getDinoBodyLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getDinoTailLookingDir");
		luaHandle->pushLUA_getDinoTailLookingDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBodyPosition");
		luaHandle->pushLUA_getDinoBodyPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadPosition");
		luaHandle->pushLUA_getDinoHeadPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTailPosition");
		luaHandle->pushLUA_getDinoTailPositionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getDinoHeadFSM");
		luaHandle->pushLUA_getDinoHeadFSMCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setDinoHeadFSM");
		luaHandle->pushLUA_setDinoHeadFSMCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "dinoSeePlayer");
		luaHandle->pushLUA_DinoSeePlayerCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "AttackPlayer");
		luaHandle->pushLUA_DinoAttackPlayerCB(S);
		lua_settable(S, -3);
		
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void ScriptC::PlayerRegister(void)
	{
		lua_newtable(S);

		lua_pushstring(S, "setPos");
		luaHandle->pushLUA_setPlayerPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "DeadState");
		luaHandle->pushLUA_playerDeadStateCB(S);
		lua_settable(S, -3);

		

		lua_pushstring(S, "EndGame");
		luaHandle->pushLUA_EndGameCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadPos");
		luaHandle->pushLUA_getPlayerHeadPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody1Pos");
		luaHandle->pushLUA_getPlayerBody1PosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody2Pos");
		luaHandle->pushLUA_getPlayerBody2PosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTailPos");
		luaHandle->pushLUA_getPlayerTailPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail1Pos");
		luaHandle->pushLUA_getPlayerTail1PosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail2Pos");
		luaHandle->pushLUA_getPlayerTail2PosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail3Pos");
		luaHandle->pushLUA_getPlayerTail3PosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getPos");
		luaHandle->pushLUA_getPlayerPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setVel");
		luaHandle->pushLUA_setPlayerVelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setHeadVel");
		luaHandle->pushLUA_setHeadVelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setBody1Vel");
		luaHandle->pushLUA_setBody1VelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setBody2Vel");
		luaHandle->pushLUA_setBody2VelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setTailVel");
		luaHandle->pushLUA_setTailVelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadVel");
		luaHandle->pushLUA_getHeadVelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody1Vel");
		luaHandle->pushLUA_getBody1VelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody2Vel");
		luaHandle->pushLUA_getBody2VelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTailVel");
		luaHandle->pushLUA_getTailVelCB(S);
		lua_settable(S, -3);


		lua_pushstring(S, "getAddedVel");
		luaHandle->pushLUA_getAddedVelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setGravityVel");
		luaHandle->pushLUA_setPlayerGravityVelCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setState");
		luaHandle->pushLUA_setPlayerStateCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getState");
		luaHandle->pushLUA_getPlayerStateCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "HeadECheck");
		luaHandle->pushLUA_playerHeadECollisionCheckCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Body1ECheck");
		luaHandle->pushLUA_playerBody1ECollisionCheckCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Body2ECheck");
		luaHandle->pushLUA_playerBody2ECollisionCheckCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "TailECheck");
		luaHandle->pushLUA_playerTailECollisionCheckCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "ECheck");
		luaHandle->pushLUA_playerECollisionCheckCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "AllCheck");
		luaHandle->pushLUA_playerAllECollisionCheckCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadCommandState");
		luaHandle->pushLUA_getHeadCommandStateCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadAssPos");
		luaHandle->pushLUA_getHeadAssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getOldHeadAssPos");
		luaHandle->pushLUA_getOldHeadAssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setOldHeadAssPos");
		luaHandle->pushLUA_setOldHeadAssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setHeadCommandState");
		luaHandle->pushLUA_setHeadCommandStateCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody1AssPos");
		luaHandle->pushLUA_getBody1AssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody2AssPos");
		luaHandle->pushLUA_getBody2AssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTailAssPos");
		luaHandle->pushLUA_getTailAssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail1AssPos");
		luaHandle->pushLUA_getTail1AssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail2AssPos");
		luaHandle->pushLUA_getTail2AssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail3AssPos");
		luaHandle->pushLUA_getTail3AssPosCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadDist");
		luaHandle->pushLUA_getHeadDistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody1Dist");
		luaHandle->pushLUA_getBody1DistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getBody2Dist");
		luaHandle->pushLUA_getBody2DistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTailDist");
		luaHandle->pushLUA_getTailDistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail1Dist");
		luaHandle->pushLUA_getTail1DistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail2Dist");
		luaHandle->pushLUA_getTail2DistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getTail3Dist");
		luaHandle->pushLUA_getTail3DistCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getHeadDir");
		luaHandle->pushLUA_getHeadDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setHeadDir");
		luaHandle->pushLUA_setHeadDirCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getEntity");
		luaHandle->pushLUA_getInactiveBlockCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "isBodyPartsMoving");
		luaHandle->pushLUA_getHeadMovingCB(S);
		lua_settable(S, -3);

		lua_setglobal(S, "Player"); // after set global .. stacks return to 0
	}

	void ScriptC::SceneRegister(void)
	{
		/* (in lua form) --
		Scene = {
		
		LoadScene(string),
		SkyboxEnable(bool),
		PlayerEnable(bool),

		}*/

		// create a new empty table and push it onto the lua-c stack 
		lua_newtable(S);

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "LoadScene");
		luaHandle->pushLUA_LoadSceneCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "SkyboxEnable");
		luaHandle->pushLUA_SkyboxEnableCB(S); // second value
		
		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "PlayerEnable");
		luaHandle->pushLUA_PlayerEnableCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "Quit");
		luaHandle->pushLUA_QuitGameCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "Restart");
		luaHandle->pushLUA_sceneRestartCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "CurrentLevel");
		luaHandle->pushLUA_CurrentLevelCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "Point");
		luaHandle->pushLUA_PointCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		//----------------------------------------------------------------------------------------
		// rmb every table has a key and a value
		// push key first .. in lua start at 1
		lua_pushstring(S, "Checkpoint");
		luaHandle->pushLUA_CheckpointCB(S); // second value

		// set the table
		// rmb once table is set .. key and value will be pop out of the stack
		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		lua_setglobal(S, "Scene"); // after set global .. stacks return to 0
	}

	void ScriptC::GraphicsSettingRegister(void)
	{
		lua_newtable(S);

		lua_pushstring(S, "SSAOEnable");
		luaHandle->pushLUA_SSAOEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "FXAAEnable");
		luaHandle->pushLUA_FXAAEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "BloomEnable");
		luaHandle->pushLUA_BloomEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "MotionBlurEnable");
		luaHandle->pushLUA_MBEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "ShadowQuality");
		luaHandle->pushLUA_ShadowQualityCB(S); 
		lua_settable(S, -3);

		lua_pushstring(S, "ShadowSize");
		luaHandle->pushLUA_ShadowSizeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "BlurBackground");
		luaHandle->pushLUA_BlurBackgroundEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Fade");
		luaHandle->pushLUA_FadeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getFade");
		luaHandle->pushgetLUA_FadeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "SceneResolution");
		luaHandle->pushLUA_getSceneResolutionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "ShadowResolution");
		luaHandle->pushLUA_getShadowResolutionCB(S);
		lua_settable(S, -3);

		lua_setglobal(S, "Graphics"); // after set global .. stacks return to 0
	}

	void ScriptC::save(ofstream& myFile, const unsigned int & guid)
	{
	}

	void ScriptC::GUIComponentRegister(void)
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

		lua_pushstring(S, "setAlpha");
		luaHandle->pushLUA_setAlpha(S);
		lua_settable(S, -3);


		lua_settable(S, -3);
	}

	void ScriptC::CanvasComponentRegister(void)
	{
		/*
		getCanvas = {
			
			setInstruction(int, bool)
			getInstruction(int)

		}*/
		lua_pushstring(S, "getCanvas");
		lua_newtable(S);

		lua_pushstring(S, "setInstruction");
		luaHandle->pushLUA_setInstructionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "getInstruction");
		luaHandle->pushLUA_getInstructionCB(S);
		lua_settable(S, -3);


		lua_settable(S, -3);
	}

	// callback functions below
	// Camera Callback Functions here
	// From here--
	int ScriptC::LUA_SetCamPositionCB(lua_State * L)
	{
		camHandle->position.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_SetCamTargetCB(lua_State * L)
	{
		camHandle->target.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_SetCamUpCB(lua_State * L)
	{
		camHandle->up.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_SetCamModeCB(lua_State * L)
	{
		int i = (int)lua_tonumber(L, 1);
		camHandle->mode = (CAMERA_MODE)i;
		return 0;
	}

	int ScriptC::LUA_SetMouseControlCB(lua_State * L)
	{
		camHandle->mouseControl = itob(lua_toboolean(L, 1));
		return 0;
	}

	int ScriptC::LUA_SetLookingDirCB(lua_State * L)
	{
		camHandle->lookingDir.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_SetMouseSensitivityCB(lua_State * L)
	{
		camHandle->MOUSE_SENSITIVITY = (float)lua_tonumber(L, 1);
		return 0;
	}

	int ScriptC::LUA_SetZoomDistanceCB(lua_State * L)
	{
		camHandle->ZOOM_DISTANCE = (float)lua_tonumber(L, 1);
		return 0;
	}

	int ScriptC::LUA_SetZoomSpeedCB(lua_State * L)
	{
		camHandle->ZOOM_SPEED = (float)lua_tonumber(L, 1);
		return 0;
	}

	int ScriptC::LUA_SetPitchLimitCB(lua_State * L)
	{
		camHandle->PITCH_LIMIT = (float)lua_tonumber(L, 1);
		return 0;
	}

	int ScriptC::LUA_SetFOVYCB(lua_State * L)
	{
		camHandle->setFOV((float)lua_tonumber(L, 1));

		return 0;
	}

	int ScriptC::LUA_SetZNearCB(lua_State * L)
	{
		camHandle->setzNear((float)lua_tonumber(L, 1));

		return 0;
	}

	int ScriptC::LUA_SetZFarCB(lua_State * L)
	{
		camHandle->setzFar((float)lua_tonumber(L, 1));

		return 0;
	}

	int ScriptC::LUA_GetCamPositionCB(lua_State * L)
	{
		vec3f pos = camHandle->position;
		lua_pushnumber(L, pos.x);
		lua_pushnumber(L, pos.y);
		lua_pushnumber(L, pos.z);

		return 3;
	}

	int ScriptC::LUA_GetCamTargetCB(lua_State * L)
	{
		vec3f tgt = camHandle->target;
		lua_pushnumber(L, tgt.x);
		lua_pushnumber(L, tgt.y);
		lua_pushnumber(L, tgt.z);

		return 3;
	}

	int ScriptC::LUA_GetCamUpCB(lua_State * L)
	{
		vec3f up = camHandle->up;
		lua_pushnumber(L, up.x);
		lua_pushnumber(L, up.y);
		lua_pushnumber(L, up.z);

		return 3;
	}

	int ScriptC::LUA_GetCamModeCB(lua_State * L)
	{
		CAMERA_MODE mode = camHandle->mode;
		lua_pushnumber(L, mode);

		return 1;
	}

	int ScriptC::LUA_GetMouseControlCB(lua_State * L)
	{
		bool mc = camHandle->mouseControl;
		lua_pushboolean(L, int(mc));

		return 1;
	}

	int ScriptC::LUA_GetLookingDirCB(lua_State * L)
	{
		vec3f lkdr = camHandle->lookingDir;
		lua_pushnumber(L, lkdr.x);
		lua_pushnumber(L, lkdr.y);
		lua_pushnumber(L, lkdr.z);

		return 3;
	}

	int ScriptC::LUA_GetMouseSensitivityCB(lua_State * L)
	{
		float ms = camHandle->MOUSE_SENSITIVITY;
		lua_pushnumber(L, ms);

		return 1;
	}

	int ScriptC::LUA_GetZoomDistanceCB(lua_State * L)
	{
		float zd = camHandle->ZOOM_DISTANCE;
		lua_pushnumber(L, zd);

		return 1;
	}

	int ScriptC::LUA_GetZoomSpeedCB(lua_State * L)
	{
		float zs = camHandle->ZOOM_SPEED;
		lua_pushnumber(L, zs);

		return 1;
	}

	int ScriptC::LUA_GetPitchLimitCB(lua_State * L)
	{
		float pl = camHandle->PITCH_LIMIT;
		lua_pushnumber(L, pl);

		return 1;
	}

	int ScriptC::LUA_GetFOVYCB(lua_State * L)
	{
		double fov = camHandle->getFOV();
		lua_pushnumber(L, fov);

		return 1;
	}

	int ScriptC::LUA_GetZNearCB(lua_State * L)
	{
		double znr = camHandle->getZNear();
		lua_pushnumber(L, znr);

		return 1;
	}

	int ScriptC::LUA_GetZFarCB(lua_State * L)
	{
		double zfr = camHandle->getZFar();
		lua_pushnumber(L, zfr);

		return 1;
	}


	// Till here--
	
	/* transform component here*/
	// from here --
	int ScriptC::LUA_TranslateCB(lua_State * L)
	{
		transformHandle->Translate(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_RotateCB(lua_State* L)
	{
		transformHandle->Rotate(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_pushRotateCB(lua_State* L)
	{
		transformHandle->pushRotation((float)lua_tonumber(L, 1), vec3f((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4)));
		return 0;
	}
	int ScriptC::LUA_RotateAroundCB(lua_State* L)
	{
		transformHandle->RotateAround(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)), vec3i((int)lua_tonumber(L, 4), (int)lua_tonumber(L, 5), (int)lua_tonumber(L, 6)), (float)lua_tonumber(L, 7));
		return 0;
	}
	int ScriptC::LUA_ScaleCB(lua_State* L)
	{
		transformHandle->Scale(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_setPositionCB(lua_State* L)
	{
		transformHandle->position.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		transformHandle->updatedFlag = true;
		return 0;
	}
	int ScriptC::LUA_getPositionCB(lua_State* L)
	{
		vec3f l = transformHandle->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_setRotationCB(lua_State* L)
	{
		transformHandle->rotation.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_getRotationCB(lua_State* L)
	{
		vec3f l = transformHandle->rotation;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_setScaleCB(lua_State* L)
	{
		transformHandle->scale.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_getScaleCB(lua_State* L)
	{
		vec3f l = transformHandle->scale;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_setLocalPositionCB(lua_State* L)
	{
		transformHandle->localPosition.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_getLocalPositionCB(lua_State* L)
	{
		vec3f l = transformHandle->localPosition;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_setLocalRotationCB(lua_State* L)
	{
		transformHandle->localRotation.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4));
		return 0;
	}
	int ScriptC::LUA_getLocalRotationCB(lua_State* L)
	{
		vec4f l = transformHandle->localRotation;
		lua_pushnumber(L, l.w);
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 4;
	}
	int ScriptC::LUA_setLocalScaleCB(lua_State* L)
	{
		transformHandle->localScale.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_getLocalScaleCB(lua_State* L)
	{
		vec3f l = transformHandle->localScale;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_LookAtCB(lua_State* L)
	{
		bool overload = itob(lua_toboolean(L, 4));

		if (overload)
		{
			transformHandle->LookAt(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)), 1);
		}
		else
		{
			transformHandle->LookAt(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)));
		}


		return 0;
	}
	int ScriptC::LUA_pushLookAtCB(lua_State* L)
	{
		transformHandle->PushLookAt(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)), (int)lua_tointeger(L, 4));
		return 0;
	}
	
	int ScriptC::LUA_setSDragRotateCB(lua_State* L)
	{
		transformHandle->specialDragonRotate.setup((float)lua_tonumber(L, 1), vec3f((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4)));
		return 0;
	}

	// Light Component Callback functions
		// From here--
	int ScriptC::LUA_SetLightPosCB(lua_State* L)
	{
		lightHandle->lightPos.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_SetLightColorCB(lua_State* L)
	{
		lightHandle->lightColor.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_SetAmbientCB(lua_State* L)
	{
		lightHandle->ambient.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_SetDiffuseCB(lua_State* L)
	{
		lightHandle->diffuse.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_SetSpecularCB(lua_State* L)
	{
		lightHandle->specular.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}

	int ScriptC::LUA_GetLightPosCB(lua_State* L)
	{
		vec3f l = lightHandle->lightPos;

		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_GetLightColorCB(lua_State* L)
	{
		vec3f l = lightHandle->lightColor;

		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_GetAmbientCB(lua_State* L)
	{
		vec3f a = lightHandle->ambient;
		lua_pushnumber(L, a.x);
		lua_pushnumber(L, a.y);
		lua_pushnumber(L, a.z);

		return 3;
	}

	int ScriptC::LUA_GetDiffuseCB(lua_State* L)
	{
		vec3f d = lightHandle->diffuse;
		lua_pushnumber(L, d.x);
		lua_pushnumber(L, d.y);
		lua_pushnumber(L, d.z);

		return 3;
	}

	int ScriptC::LUA_GetSpecularCB(lua_State* L)
	{
		vec3f s = lightHandle->specular;
		lua_pushnumber(L, s.x);
		lua_pushnumber(L, s.y);
		lua_pushnumber(L, s.z);

		return 3;
	}
	
	// till here --



	/* trigger component related */
	// from here--
	int ScriptC::LUA_isTriggerCB(lua_State* L)
	{
		lua_pushboolean(L, triggerhandle->alerts[(int)lua_tointeger(L, 1)]);
		return 1;
	}
	int ScriptC::LUA_setTriggerCB(lua_State* L)
	{
		triggerhandle->alerts[(int)lua_tointeger(L, 1)] = itob(lua_toboolean(L, 2));
		return 0;
	}

	// till here

	/* AABB component related */
	// from here--
	int ScriptC::LUA_setPosCB(lua_State* L) 
	{
		std::string tag = lua_tostring(L, 1);
		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->isTag(tag))
			{
				aabb = x;
				break;
			}
		}

		aabb->setPos(vec3f((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4)));

		return 0;
	}
	int ScriptC::LUA_setHalfSizeCB(lua_State* L) 
	{
		std::string tag = lua_tostring(L, 1);
		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->isTag(tag))
			{
				aabb = x;
				break;
			}
		}

		aabb->setHalfSize(vec3f((float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4)));
		return 0;
	}
	int ScriptC::LUA_getMinCB(lua_State* L) 
	{
		std::string tag = lua_tostring(L, 1);
		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->isTag(tag))
			{
				aabb = x;
				break;
			}
		}

		if (aabb)
		{
			vec3f l = aabb->getMin();

			lua_pushnumber(L, l.x);
			lua_pushnumber(L, l.y);
			lua_pushnumber(L, l.z);
		}

		else
		{
			lua_pushnumber(L, 0);
			lua_pushnumber(L, 0);
			lua_pushnumber(L, 0);
		}

		return 3;
	}
	int ScriptC::LUA_getMaxCB(lua_State* L) 
	{
		std::string tag = lua_tostring(L, 1);
		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->isTag(tag))
			{
				aabb = x;
				break;
			}
		}

		if (aabb)
		{
			vec3f l = aabb->getMax();

			lua_pushnumber(L, l.x);
			lua_pushnumber(L, l.y);
			lua_pushnumber(L, l.z);
		}

		else
		{
			lua_pushnumber(L, 0);
			lua_pushnumber(L, 0);
			lua_pushnumber(L, 0);
		}

		return 3;
	}
	int ScriptC::LUA_getRPosCB(lua_State* L)
	{
		std::string tag = lua_tostring(L, 1);
		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->isTag(tag))
			{
				aabb = x;
				break;
			}
		}

		if (aabb)
		{
			vec3f l = aabb->getRPos();

			lua_pushnumber(L, l.x);
			lua_pushnumber(L, l.y);
			lua_pushnumber(L, l.z);
		}

		else
		{
			lua_pushnumber(L, 0);
			lua_pushnumber(L, 0);
			lua_pushnumber(L, 0);
		}
		
		return 3;
	}
	int ScriptC::LUA_setAABBCollideCB(lua_State* L)
	{
		std::string tag = lua_tostring(L, 1);
		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->isTag(tag))
			{
				aabb = x;
				break;
			}
		}


		if (aabb) aabb->setCollide(itob(lua_toboolean(L, 1)));
		else lua_pushboolean(L, false);

		return 0;
	}
	int ScriptC::LUA_isAABBCollideCB(lua_State* L)
	{
		unsigned int guid = (unsigned int)lua_tonumber(L, 1);

		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->guid == guid)
			{
				aabb = x;
				break;
			}
		}

		if (aabb) lua_pushboolean(L, aabb->isCollide());
		else lua_pushboolean(L, false);

		return 1;
	}
	int ScriptC::LUA_checkAABBCollideCB(lua_State* L)
	{
		unsigned int guid = (unsigned int)lua_tonumber(L, 1);
		std::string tagtocollide = lua_tostring(L, 2);

		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->guid == guid)
			{
				aabb = x;
				break;
			}
		}

		componentsDaddy->AABBvsAABBs(*aabb, tagtocollide);
		playerHandle->allComponents->AABBvsAABBs(*aabb, tagtocollide);

		if (aabb) lua_pushboolean(L, aabb->isCollide());
		else lua_pushboolean(L, false);

		return 1;
	}
	int ScriptC::LUA_getAABBCollideInfoCB(lua_State* L)
	{
		unsigned int guid = (unsigned int)lua_tonumber(L, 1);

		AABB* aabb = nullptr;

		for (auto &x : aabbHandles)
		{
			if (x->guid == guid)
			{
				aabb = x;
				break;
			}
		}

		if (aabb) lua_pushinteger(L, aabb->intersectInfo);
		else lua_pushboolean(L, false);

		return 1;
	}

	// till here--
	

	// Direction Light Callback functions here
	// From here--
	int ScriptC::LUA_SetLightDirectionCB(lua_State* L)
	{
		dirlightHandle->lightdirection.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_GetLightDirectionCB(lua_State* L)
	{
		vec3f l = dirlightHandle->lightdirection;

		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_ChangeLightDirectionCB(lua_State* L)
	{
		dirlightHandle->changeLightDir(vec3f((float)lua_tonumber(L, 1),
			(float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)), // rotation
			(float)lua_tonumber(L, 4)); // angle

		return 0;
	}

	int ScriptC::LUA_StartLineCB(lua_State * L)
	{
		linerendererhandle->setPos(vec3f((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3))));
		return 0;
	}

	int ScriptC::LUA_EndLineCB(lua_State * L)
	{
		linerendererhandle->setTar(vec3f((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3))));
		return 0;
	}

	// Till here--
	

	// Renderer callback functions
	// From here--
	int ScriptC::LUA_SetColorCB(lua_State* L)
	{
		rendererHandle->color.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_SetEmissiveCB(lua_State* L)
	{
		rendererHandle->emissive = (float)lua_tonumber(S, 1);
		return 0;
	}
	int ScriptC::LUA_SetShininessCB(lua_State* L)
	{
		rendererHandle->shininess = (float)lua_tonumber(S, 1);
		return 0;
	}
	int ScriptC::LUA_SetObjectVisibilityCB(lua_State* L)
	{
		rendererHandle->enabled = itob(lua_toboolean(S, 1));
		return 0;
	}
	int ScriptC::LUA_SetMeshNameCB(lua_State* L)
	{
		rendererHandle->meshName = lua_tostring(S, 1);
		return 0;
	}
	int ScriptC::LUA_GetColorCB(lua_State* L)
	{
		vec3f r = rendererHandle->color;
		lua_pushnumber(L, r.x);
		lua_pushnumber(L, r.y);
		lua_pushnumber(L, r.z);

		return 3;
	}
	int ScriptC::LUA_GetEmissiveCB(lua_State* L)
	{
		lua_pushnumber(L, rendererHandle->emissive);
		return 1;
	}
	int ScriptC::LUA_GetShininessCB(lua_State* L)
	{
		lua_pushnumber(L, rendererHandle->shininess);
		return 1;
	}
	int ScriptC::LUA_GetObjectVisibilityCB(lua_State* L)
	{
		lua_pushboolean(L, rendererHandle->enabled);
		return 1;
	}
	int ScriptC::LUA_GetMeshNameCB(lua_State* L)
	{
		lua_pushstring(L, rendererHandle->meshName.c_str());
		return 1;
	}
	// Till here

	/* Sphere collider component related */
	// from here--
	int ScriptC::LUA_setfradiusCB(lua_State* L) 
	{
		spherecolliderHandle->setfradius((float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_getfradiusCB(lua_State* L) 
	{
		lua_pushnumber(L, spherecolliderHandle->getfradius());
		return 1;
	}
	int ScriptC::LUA_setSphereCollideCB(lua_State* L) 
	{
		spherecolliderHandle->setCollide(itob(lua_toboolean(L, 1)));
		return 0;
	}
	int ScriptC::LUA_isSphereCollideCB(lua_State* L) 
	{
		lua_pushboolean(L, spherecolliderHandle->isCollide());
		return 1;
	}
	// till here--

	/* ellipsoid collider component related */
	// from here--
	int ScriptC::LUA_setEllipsoidR3GravityCB(lua_State* L)
	{
		ellipsoidHandle->R3gravity.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_setEllipsoidRadiusCB(lua_State * L)
	{
		ellipsoidHandle->eRadius.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_setEllipsoidR3VelCB(lua_State * L)
	{
		ellipsoidHandle->R3Velocity.Set((float)(lua_tonumber(L, 1)), (float)(lua_tonumber(L, 2)), (float)(lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_getEllipsoidR3GravityCB(lua_State* L)
	{
		vec3f g = ellipsoidHandle->R3gravity;
		lua_pushnumber(L, g.x);
		lua_pushnumber(L, g.y);
		lua_pushnumber(L, g.z);

		return 3;
	}
	int ScriptC::LUA_getEllipsoidRadiusCB(lua_State * L)
	{
		vec3f r = ellipsoidHandle->eRadius;
		lua_pushnumber(L, r.x);
		lua_pushnumber(L, r.y);
		lua_pushnumber(L, r.z);

		return 3;
	}
	int ScriptC::LUA_getEllipsoidR3VelCB(lua_State * L)
	{
		vec3f r = ellipsoidHandle->R3Velocity;
		lua_pushnumber(L, r.x);
		lua_pushnumber(L, r.y);
		lua_pushnumber(L, r.z);

		return 3;
	}
	int ScriptC::LUA_isEllipsoidCollideCB(lua_State * L)
	{
		if (itob(lua_toboolean(L, 1)) == true)
		{
			lua_pushboolean(L, ellipsoidHandle->foundCollision);
		}
		else
		{
			lua_pushboolean(L, ellipsoidHandle->foundCollisionGravity);
		}
		return 1;
	}
	int ScriptC::LUA_EllipsoidCollisionCheckCB(lua_State * L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(ellipsoidHandle, (float)lua_tonumber(L, 1));
		return 0;
	}
	// till here--

	/* keyboard & mouse component related */
	// from here--
	int ScriptC::LUA_isKeyPressedCB(lua_State* L)
	{
		lua_pushboolean(L, keyboardHandle->isKeyPressed((KEY)lua_tointeger(L, 1)));
		return 1;
	}
	int ScriptC::LUA_isKeyHoldCB(lua_State* L)
	{
		lua_pushboolean(L, keyboardHandle->isKeyHold((KEY)lua_tointeger(L, 1)));
		return 1;
	}
	int ScriptC::LUA_isKeyTouchedCB(lua_State* L)
	{
		lua_pushboolean(L, keyboardHandle->isKeyTouched((KEY)lua_tointeger(L, 1)));
		return 1;
	}
	int ScriptC::LUA_isMouseClickCB(lua_State* L)
	{
		lua_pushboolean(L, mouseHandle->isClick((MOUSE)lua_tointeger(L, 1)));
		return 1;
	}
	int ScriptC::LUA_isMouseHoldCB(lua_State* L)
	{
		lua_pushboolean(L, mouseHandle->isHold((MOUSE)lua_tointeger(L, 1)));
		return 1;
	}
	int ScriptC::LUA_getScrollingCB(lua_State* L)
	{
		lua_pushnumber(L, mouseHandle->getScrolling());
		return 1;
	}
	int ScriptC::LUA_setCursorEnableCB(lua_State * L)
	{
		sceneHandle->LUA_setCursorEnableCB(L);
		return 0;
	}
	int ScriptC::LUA_getCursorPositionCB(lua_State * L)
	{
		vec3f cursorPos(mouseHandle->cursorPosFont.x, mouseHandle->cursorPosFont.y, 0);
		lua_pushnumber(L, cursorPos.x);
		lua_pushnumber(L, cursorPos.y);
		return 2;
	}
	int ScriptC::LUA_CursorVsGUIAABBCB(lua_State * L)
	{
		daddy->cursorPosVSAABBs();
		return 0;
	}
	// till here--


	/* player callback functions here*/
	// from here--

	int ScriptC::LUA_SSAOEnableCB(lua_State * L)
	{
		if (lua_isstring(L, 1))
		{
			lua_pushboolean(L, sceneHandle->goption->isssaoEnable());
			return 1;
		}

		else
		{
			sceneHandle->goption->setssaoEnable(itob(lua_toboolean(L, 1)));
			sceneHandle->goption->setUpdateFlag(true);
		}
		return 0;
	}

	int ScriptC::LUA_FXAAEnableCB(lua_State * L)
	{
		if (lua_isstring(L, 1))
		{
			lua_pushboolean(L, sceneHandle->goption->isfxaa_enable());
			return 1;
		}

		else
		{
			sceneHandle->goption->setfxaa_enable(itob(lua_toboolean(L, 1)));
			sceneHandle->goption->setUpdateFlag(true);
		}
		return 0;
	}

	int ScriptC::LUA_BloomEnableCB(lua_State * L)
	{
		if (lua_isstring(L, 1))
		{
			lua_pushboolean(L, sceneHandle->goption->isbloomEnable());
			return 1;
		}

		else
		{
			sceneHandle->goption->setbloomEnable(itob(lua_toboolean(L, 1)));
			sceneHandle->goption->setUpdateFlag(true);
		}
		return 0;
	}

	int ScriptC::LUA_MBEnableCB(lua_State * L)
	{
		if (lua_isstring(L, 1))
		{
			lua_pushboolean(L, sceneHandle->goption->ismotionBlurEnable());
			return 1;
		}

		else
		{
			sceneHandle->goption->setmotionBlurEnable(itob(lua_toboolean(L, 1)));
			sceneHandle->goption->setUpdateFlag(true);
		}
		return 0;
	}

	int ScriptC::LUA_ShadowQualityCB(lua_State * L)
	{

		return 0;
	}

	int ScriptC::LUA_ShadowSizeCB(lua_State * L)
	{
		DirLightC::lightprojsize = (double)lua_tonumber(L, 1);
		return 0;
	}

	int ScriptC::LUA_BlurBackgroundEnableCB(lua_State * L)
	{
		sceneHandle->goption->setlow_resblurenable(itob(lua_toboolean(L, 1)));
		return 0;
	}

	int ScriptC::LUA_FadeCB(lua_State * L)
	{
		sceneHandle->goption->setFadeValue((float)lua_tonumber(L, 1));
		return 0;
	}

	int ScriptC::getLUA_FadeCB(lua_State * L)
	{
		lua_pushnumber(L, sceneHandle->goption->getFadeValue());
		return 1;
	}

	int ScriptC::LUA_QuitGameCB(lua_State * L)
	{
		sceneHandle->exit = true;
		return 0;
	}

	int ScriptC::LUA_sceneRestartCB(lua_State * L)
	{
		if (lua_isstring(L, 1))
			sceneHandle->RestartScene(lua_tostring(L, 1));
		else
			sceneHandle->activeScene->restartFlag = true;
		return 0;
	}

	int ScriptC::LUA_getSceneResolutionCB(lua_State * L)
	{
		if (lua_isnumber(L, 1))
		{
			vec2i reso = vec2i((int)lua_tonumber(S, 1), (int)lua_tonumber(S, 2));
			sceneHandle->goption->setResolution(reso);
			GraphicScale* g = sceneHandle->goption;

			if (reso.x == 1080)
			{
				g->setssaoKernel(4);
				g->setblurRadius(6);
				g->setblurSize(6);
			}
				
			else if (reso.x == 1280)
			{
				g->setssaoKernel(16);
				g->setblurRadius(10);
				g->setblurSize(10);
			}
				
			else
			{
				g->setssaoKernel(32);
				g->setblurRadius(10);
				g->setblurSize(10);
			}
				
			gHandle->initFBO();
			sceneHandle->goption->setUpdateFlag(true);
		}
		else
		{
			vec2i r = sceneHandle->goption->getResolution();

			lua_pushnumber(L, r.x);
			lua_pushnumber(L, r.y);

			return 2;
		}

		return 0;
	}

	int ScriptC::LUA_getShadowResolutionCB(lua_State * L)
	{
		if (lua_isnumber(L, 1))
		{
			sceneHandle->goption->setShadowResolution(vec2i((int)lua_tonumber(S, 1), (int)lua_tonumber(S, 2)));
			gHandle->resetShadowMap();
		}
		else
		{
			vec2i r = sceneHandle->goption->getShadowResolution();

			lua_pushnumber(L, r.x);
			lua_pushnumber(L, r.y);

			return 2;
		}

		return 0;
	}

	int ScriptC::LUA_setPlayerPosCB(lua_State * L)
	{
		playerHandle->player[(int)lua_tointeger(L, 1)]->transformC->position.Set( (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3), (float)lua_tonumber(L, 4) );
		return 0;
	}

	int ScriptC::LUA_getPlayerHeadPosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[HEAD]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerBody1PosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[BODY1]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerBody2PosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[BODY2]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerTailPosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[TAIL]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerTail1PosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[TAIL1]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerTail2PosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[TAIL2]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerTail3PosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[TAIL3]->transformC->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getPlayerPosCB(lua_State* L)
	{
		vec3f l = playerHandle->player[playerHandle->PlayerControlState]->findComponentT<TransformationC>()->position;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_setPlayerVelCB(lua_State* L)
	{
		playerHandle->player[playerHandle->PlayerControlState]->findComponentT<EllipsoidColliderC>()->R3Velocity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_setHeadVelCB(lua_State* L)
	{
		EllipsoidColliderC* e = playerHandle->player[HEAD]->findComponentT<EllipsoidColliderC>();
		e->R3Velocity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		e->R3gravity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_setBody1VelCB(lua_State* L)
	{
		EllipsoidColliderC* e = playerHandle->player[BODY1]->findComponentT<EllipsoidColliderC>();
		e->R3Velocity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		e->R3gravity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_setBody2VelCB(lua_State* L)
	{
		EllipsoidColliderC* e = playerHandle->player[BODY2]->findComponentT<EllipsoidColliderC>();
		e->R3Velocity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		e->R3gravity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_setTailVelCB(lua_State* L)
	{
		EllipsoidColliderC* e = playerHandle->player[TAIL]->findComponentT<EllipsoidColliderC>();
		e->R3Velocity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		e->R3gravity.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}
	int ScriptC::LUA_getHeadVelCB(lua_State* L)
	{
		vec3f l = playerHandle->dragonass[HEAD].addedVel;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getBody1VelCB(lua_State* L)
	{
		vec3f l = playerHandle->dragonass[BODY1].addedVel;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getBody2VelCB(lua_State* L)
	{
		vec3f l = playerHandle->dragonass[BODY2].addedVel;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getTailVelCB(lua_State* L)
	{
		vec3f l = playerHandle->dragonass[TAIL].addedVel;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_getAddedVelCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[playerHandle->PlayerControlState].addedVel;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}


	int ScriptC::LUA_setPlayerGravityVelCB(lua_State * L)
	{
		//playerHandle->gravitySet(vec3f((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3)));
		return 0;
	}
	int ScriptC::LUA_playerDeadStateCB(lua_State * L)
	{
		if (lua_isstring(L, 1))
		{
			lua_pushboolean(L, playerHandle->dead);
			return 1;
		}

		playerHandle->dead = itob(lua_toboolean(L, 1));

		return 0;
	}
	int ScriptC::LUA_EndGameCB(lua_State * L)
	{
		if (!lua_isboolean(L, 1))
		{
			lua_pushboolean(L, playerHandle->endgame);
			return 1;
		}
		else
		{
			playerHandle->endgame = itob(lua_toboolean(L, 1));
		}
		return 0;
	}
	int ScriptC::LUA_setPlayerStateCB(lua_State* L)
	{
		playerHandle->PlayerControlState = (PLAYER_CONTROL_STATE)lua_tointeger(L, 1);
		return 0;
	}
	int ScriptC::LUA_getPlayerStateCB(lua_State* L)
	{
		lua_pushnumber(L, playerHandle->PlayerControlState);
		return 1;
	}
	int ScriptC::LUA_playerHeadECollisionCheckCB(lua_State* L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[HEAD]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_playerBody1ECollisionCheckCB(lua_State* L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[BODY1]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_playerBody2ECollisionCheckCB(lua_State* L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[BODY2]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_playerTailECollisionCheckCB(lua_State* L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[TAIL]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_playerECollisionCheckCB(lua_State* L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[playerHandle->PlayerControlState]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_playerAllECollisionCheckCB(lua_State* L)
	{
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[HEAD]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[BODY1]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[BODY2]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		componentsDaddy->EllipsoidCollideAndSlide(playerHandle->player[TAIL]->findComponentT<EllipsoidColliderC>(), (float)lua_tonumber(L, 1));
		return 0;
	}
	int ScriptC::LUA_getHeadCommandStateCB(lua_State * L)
	{
		lua_pushnumber(L, (int)playerHandle->headCommandState);
		return 1;
	}
	int ScriptC::LUA_getHeadAssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[HEAD].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getOldHeadAssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[HEAD].oldAssPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_setOldHeadAssPosCB(lua_State * L)
	{
		playerHandle->dragonass[HEAD].oldAssPos.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_setHeadCommandStateCB(lua_State * L)
	{
		playerHandle->headCommandState = (LEADER_HEAD_COMMAND)lua_tointeger(L, 1);

		return 0;
	}
	int ScriptC::LUA_getBody1AssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[BODY1].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getBody2AssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[BODY2].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getTailAssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[TAIL].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getTail1AssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[TAIL1].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);
		return 3;
	}
	int ScriptC::LUA_getTail2AssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[TAIL2].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getTail3AssPosCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[TAIL3].assPos;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_getHeadDistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[HEAD].distance);
		return 1;
	}
	int ScriptC::LUA_getBody1DistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[BODY1].distance);
		return 1;
	}
	int ScriptC::LUA_getBody2DistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[BODY2].distance);
		return 1;
	}
	int ScriptC::LUA_getTailDistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[TAIL].distance);
		return 1;
	}
	int ScriptC::LUA_getTail1DistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[TAIL1].distance);
		return 1;
	}
	int ScriptC::LUA_getTail2DistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[TAIL2].distance);
		return 1;
	}
	int ScriptC::LUA_getTail3DistCB(lua_State * L)
	{
		lua_pushnumber(L, playerHandle->dragonass[TAIL3].distance);
		return 1;
	}

	int ScriptC::LUA_getHeadDirCB(lua_State * L)
	{
		vec3f l = playerHandle->dragonass[HEAD].direction;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_setHeadDirCB(lua_State * L)
	{
		playerHandle->dragonass[HEAD].direction.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_getHeadMovingCB(lua_State * L)
	{
		PLAYER_CONTROL_STATE state = (PLAYER_CONTROL_STATE)lua_tointeger(L, 1);

		if(state == HEAD)
			lua_pushboolean(L, playerHandle->isHeadMoving);
		else if (state == TAIL)
			lua_pushboolean(L, playerHandle->isTailMoving);

		return 1;
	}

	// till here--

	int ScriptC::LUA_LoadSceneCB(lua_State * L)
	{
		sceneHandle->changeScene(lua_tostring(L, 1));
		return 0;
	}

	int ScriptC::LUA_CurrentLevelCB(lua_State * L)
	{
		if (!lua_isstring(L, 1))
		{
			lua_pushstring(L, sceneHandle->WhichScene.c_str());
			return 1;

		}
		else
		{
			sceneHandle->WhichScene = lua_tostring(L, 1);
		}
		return 0;
	}

	// from here--
	int ScriptC::LUA_setDinoHeadLookingDirCB(lua_State* L)
	{
		dinoAIHandle->dinoHeadLookingDir.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_setDinoBodyLookingDirCB(lua_State* L)
	{
		dinoAIHandle->dinoBodyLookingDir.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_setDinoTailLookingDirCB(lua_State* L)
	{
		dinoAIHandle->dinoTailLookingDir.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		return 0;
	}

	int ScriptC::LUA_getDinoHeadLookingDirCB(lua_State* L)
	{
		vec3f l = dinoAIHandle->dinoHeadLookingDir;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_getDinoBodyLookingDirCB(lua_State* L) 
	{
		vec3f l = dinoAIHandle->dinoBodyLookingDir;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_getDinoTailLookingDirCB(lua_State* L)
	{
		vec3f l = dinoAIHandle->dinoTailLookingDir;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_getDinoHeadPositionCB(lua_State* L)
	{
		vec3f l = *dinoAIHandle->HeadPosition;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}
	int ScriptC::LUA_getDinoBodyPositionCB(lua_State* L)
	{
		vec3f l = *dinoAIHandle->BodyPosition;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;
	}

	int ScriptC::LUA_getDinoTailPositionCB(lua_State* L)
	{
		/*vec3f l = *dinoAIHandle->TailPosition;
		lua_pushnumber(L, l.x);
		lua_pushnumber(L, l.y);
		lua_pushnumber(L, l.z);

		return 3;*/

		return 0;
	}

	int ScriptC::LUA_getDinoHeadFSMCB(lua_State* L)
	{
		lua_pushnumber(L, (int)dinoAIHandle->dinoHeadFSM);
		return 1;
	}

	int ScriptC::LUA_setDinoHeadFSMCB(lua_State* L)
	{
		dinoAIHandle->dinoHeadFSM = (DINOHEAD_FSM)lua_tointeger(L, 1);
		return 0;
	}

	int ScriptC::LUA_DinoSeePlayerCB(lua_State* L)
	{
		lua_pushboolean(L, dinoAIHandle->seePlayer[(int)lua_tointeger(L, 1)]);

		return 1;
	}

	int ScriptC::LUA_DinoAttackPlayerCB(lua_State* L)
	{
		dinoAIHandle->attackPlayer = itob(lua_toboolean(L, 1));
		return 0;
	}
	// till here--

	// UI related
	// from here --
	int ScriptC::LUA_SkyboxEnableCB(lua_State * L)
	{
		gHandle->skyboxEnable = itob(lua_toboolean(L, 1));
		return 0;
	}
	int ScriptC::LUA_PlayerEnableCB(lua_State * L)
	{
		playerHandle->updateMah = itob(lua_toboolean(L, 1));
		return 0;
	}
	int ScriptC::LUA_setTextString(lua_State * L)
	{
		guiHandle->setTextString(lua_tostring(L, 1));
		return 0;
	}

	int ScriptC::LUA_setTextColor(lua_State * L)
	{
		guiHandle->setColor((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
		guiHandle->setAlpha((float)lua_tonumber(L, 4));
		return 0;
	}

	int ScriptC::LUA_setTextMaterial(lua_State * L)
	{
		FontMaterial& m = guiHandle->material;
		m.width = (float)lua_tonumber(L, 1);
		m.edge = (float)lua_tonumber(L, 2);
		m.borderwidth = (float)lua_tonumber(L, 3);
		m.borderedge = (float)lua_tonumber(L, 4);
		m.offsetx = (float)lua_tonumber(L, 5);
		m.offsety = (float)lua_tonumber(L, 6);
		m.coloroutline.Set((float)lua_tonumber(L, 7), (float)lua_tonumber(L, 8), (float)lua_tonumber(L, 9));
		return 0;
	}

	int ScriptC::LUA_setFontType(lua_State * L)
	{
		guiHandle->setFontType(FontsLibrary::getInstance()->FontTypes[lua_tostring(L, 1)]);
		return 0;
	}

	int ScriptC::LUA_setMaxLine(lua_State * L)
	{
		guiHandle->setMaxLineSize((float)lua_tonumber(L, 1));
		return 0;
	}

	int ScriptC::LUA_setAlpha(lua_State * L)
	{
		guiHandle->setAlpha((float)lua_tonumber(L, 1));
		return 0;
	}
	// till here --

	/* Canvas related */
	// From here --
	int ScriptC::LUA_setInstructionCB(lua_State * L)
	{
		int index = (int)lua_tointeger(L, 1);
		canvasHandle->instruction[index] = itob(lua_toboolean(L, 2));

		return 0;
	}

	int ScriptC::LUA_getInstructionCB(lua_State * L)
	{
		int index = (int)lua_tointeger(L, 1);
		lua_pushboolean(L, canvasHandle->instruction[index]);
		return 1;
	}
	// Till here --
	
	int ScriptC::LUA_getInactiveBlockCB(lua_State* L)
	{
		getOwner()->bigDaddy->FindNotActiveEntity(lua_tostring(L, 1));
		return 0;
	}


	int ScriptC::LUA_PointCB(lua_State * L)
	{
		lua_pushinteger(L, sceneHandle->activeScene->point);
		lua_pushnumber(L, sceneHandle->activeScene->playingtime);
		return 2;
	}

	int ScriptC::LUA_CheckpointCB(lua_State * L)
	{
		if (lua_isboolean(L, 1))
		{
			vec3f l = sceneHandle->activeScene->checkpoint;
			lua_pushnumber(L, l.x);
			lua_pushnumber(L, l.y);
			lua_pushnumber(L, l.z);

			sceneHandle->activeScene->point -= 500;

			if (sceneHandle->activeScene->point < 0)
				sceneHandle->activeScene->point = 0;

			return 3;
		}
		else
		{
			sceneHandle->activeScene->checkpoint.Set((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2), (float)lua_tonumber(L, 3));
			return 0;
		}
		
	}


	// End here--
}
