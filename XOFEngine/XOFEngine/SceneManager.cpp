#include "SceneManager.h"
#include "gl_backend.h"
#include "scenebase.h"
#include "utils.h"
#include "engine_common.h"
#include "GraphicScale.h"

#include "Scene3D.h"

#include "Mouse.h"
#include "Keyboard.h"

#include "lua\lua.hpp"
#include "lua_backend.h"

#include "GUIrenderEngine.h"

#include "SphereColliderC.h"
#include "CameraC.h"

#include "ComponentsPool.h"

#include "GraphicEngine.h"

#include "World.h"

#include "GLFW_Window.h"

#include "PlayerManager.h"

#include "DirLightC.h"

namespace pp
{
	scenebase* SceneManager::activeScene = nullptr;
	SceneManager* SceneManager::s_instance = nullptr;
	static bool continueForChangingScene = false;

	SceneManager::SceneManager(void) : 
		mouseHandle(nullptr), 
		BackEndHandle(nullptr), 
		keyboardHandle(nullptr), 
		S(nullptr), 
		luaHandle(nullptr), 
		guiHandle(nullptr), 
		pickerHandle(nullptr),
		windowHandle(nullptr),
		graphicsHandle(nullptr),
		goption(nullptr),
		playerHandle(nullptr),
		WhichScene("none")
	{
		// just a handle
		windowHandle = GLFW_Window::getInstance();
		mouseHandle = Mouse::getInstance();
		BackEndHandle = gl_backend::getInstance();
		keyboardHandle = Keyboard::getInstance();
		guiHandle = GUIrenderEngine::getInstance();
		luaHandle = lua_backend::getInstance();
		graphicsHandle = GraphicEngine::getInstance();
		playerHandle = PlayerManager::getInstance();
	}

	SceneManager::~SceneManager(void)
	{
		terminate();
	}

	void SceneManager::setUp(void)
	{
		// prevent memory leak
		terminate();

		initGoption();
		luaSetUp();
		graphicsHandle->setGoption(this->goption);
		// set up the graphic engine
		graphicsHandle->setUp();
		guiHandle->setUp();
	}

	void SceneManager::luaSetUp(void)
	{
		// set up
		S = luaL_newstate();
		luaL_openlibs(S);

		// registration
		luaRegistration(); // register all the lua functions ..

		// execution 
		int i = luaL_dofile(S, "Content//assets//AppInit.lua");

		// confirm need to have init function
		lua_getglobal(S, "Init");

		// after this pcall .. above stack will be remove 
		if (lua_pcall(S, 0, 0, 0) != EXIT_SUCCESS) // 1 arguments, 0 return
		{
			printf("error running function printMsg \n");
			lua_close(S);
		}
	}

	void SceneManager::luaRegistration(void)
	{
		// tell the lua that we are ready to register pls
		luaHandle->setCallBack(this);

		/* (in lua form) -- Graphics = {

		SSAO = { 
		Enable(), 
		KernelSize(), 
		Radius(), 
		Strength() 
		},

		MotionBlur = { 
		Enable(), 
		MaxSample(), 
		Scale() 
		},

		Bloom = { 
		Enable(), 
		BlurRadius(), 
		BlurSize() 
		},

		FXAA = { 
		Enable(), 
		Size() 
		},

		LensFlare = { 
		Enable(), 
		Scale(), 
		Bias(), 
		Distortion(), 
		Ghost(), 
		GhostDisperal(), 
		HaloWidth() 
		},

		DebugMesh{ 
		Sphere(), 
		AABB() 
		}

		}*/

		// create a new empty table and push it onto the lua-c stack 
		lua_newtable(S);

		SSAOGSLuaRegister();
		debugMeshLuaRegister();
		LensFlareGSLuaRegister();
		FXAAGSLuaRegister();
		BloomGSLuaRegister();
		MotionBlurGSLuaRegister();

		lua_setglobal(S, "Graphics"); // after set global .. stacks return to 0

		// added a new save scene function into the lua
		luaHandle->pushLUA_SaveSceneCB(S);
		lua_setglobal(S, "SaveScene");

		// added a new load scene function into the lua
		luaHandle->pushLUA_LoadSceneCB(S);
		lua_setglobal(S, "Restart");

		// added a new load scene function into the lua
		luaHandle->pushLUA_setCursorEnableCB(S);
		lua_setglobal(S, "CursorEnable");

		/* (in lua form) -- App = { 
		window = {
		setSize(int , int), 
		setFullScreen(bool) 
		}, 
		scene = {
		create(string, string), 
		LoadScene(string)} 
		} */

		// create a new empty table and push it onto the lua-c stack 
		lua_newtable(S);

		// window properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "window");
		lua_newtable(S);

		lua_pushstring(S, "setSize");
		luaHandle->pushLUA_setWindowSizeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "setFullScreen");
		luaHandle->pushLUA_setWindowFullScreenCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------

		// scene properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "scene");
		lua_newtable(S);

		lua_pushstring(S, "create");
		luaHandle->pushLUA_createSceneCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "LoadScene");
		luaHandle->pushLUA_setActiveSceneCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		lua_setglobal(S, "App"); // after set global .. stacks return to 0
	}

	void SceneManager::initGoption(void)
	{
		if (goption == nullptr)
		{
			goption = new GraphicScale();
		}

		// medium setting
		goption->setfxaa_Size(2);

		goption->setblurRadius(10);  // change for better performance
		goption->setblurSize(10);  // change for better performance

		goption->setlensFScale(2.f);  // visibility of the lensflare
		goption->setlensFBias(-0.5f);  // distance 
		goption->setlensFDistortion(1.5f);  // change for better performance

		goption->setlensFGhost(8);
		goption->setlensFGhostDispersal(0.16f);
		goption->setlensFHaloWidth(0.6f);

		goption->setssaoKernel(16);  // change for better performance
		goption->setssaoRadius(1.f);
		goption->setssaoStrength(1.0f);

		goption->setmotionblur_maxsample(32); // change for better performance
		goption->setmotionblur_framerate(1.f / 40.f);

		goption->setlensFEnable(true);
		goption->setssaoEnable(true);
		goption->setlow_resblurenable(false);
		goption->setbloomEnable(true);
		goption->setmotionBlurEnable(true);
		goption->setfxaa_enable(true);

		goption->setDebugMeshRenderSphere(false);
		goption->setDebugMeshRenderAABB(false);
	}

	void SceneManager::run(void)
	{
		// init all callbacks, rmb glew and window init before hand
		BackEndHandle->GLBackendRun(this);

		// start the timer // once started once .. forever started
		startTimer();

		CameraC* camera = ComponentsPool::cameraComponent;

		// main loop start here
		while (!exit)
		{
			// calc the dt and fps of the prev scene
			calcFPS();

			// inputs update
			InputUpdate();

			// scene update
			activeScene->update(deltaTime);

			if (continueForChangingScene)
			{
				continueForChangingScene = false;
				continue;
			}
			// player update
			playerHandle->Update(deltaTime);

			// camera update
			camera->update(deltaTime);

			// scene render
			activeScene->render();
			
			playerHandle->lateUpdate(deltaTime);

			// scene update after render
			activeScene->lateupdate(deltaTime);

			// swap buffers 
			BackEndHandle->GLSwapBuffers();

			// wait for constant fps

			TimerShldWait();
		}
	}

	void SceneManager::InputUpdate(void)
	{
		// mouse input reset for prev frame
		mouseHandle->resetKeyPressed();
		mouseHandle->setScrolling(0);
		
		// poll the events baby
		BackEndHandle->GLPollEvents();

		// mouse cursor update
		mouseHandle->updatePitchAndYaw(deltaTime);
		mouseHandle->updateMouseCursorFontSpace((float)windowHandle->getWindowWidth(), (float)windowHandle->getWindowHeight(), deltaTime);

		// mouse picker update
		// pickerHandle->update();
	}

	void SceneManager::addScene(const string & sceneName, const string & worldPath)
	{
		static int recursive = 0;

		auto f = scenes.find(sceneName);

		// if it is an entirely new scene
		if (f == scenes.end())
		{
			// remember to set the recursive back to 0
			recursive = 0;

			scenes[sceneName] = new Scene3D(sceneName, "Content//assets//" + worldPath);
			if (!scenes[sceneName]->Init())
			{
				printf("%s not init properly dude", sceneName);
				throw(0);
			}
			
			printf("%s added \n", sceneName.c_str());
		}

		// if not .. change the name and repeat it
		else
		{
			recursive++;
			addScene(sceneName + std::to_string(recursive), worldPath);
		}
	}

	void SceneManager::changeScene(const string & sceneName)
	{
		auto f = scenes.find(sceneName);

		// if it is a valid scene
		if (f != scenes.end())
		{
			continueForChangingScene = true;
			keyboardHandle->resetAllKeys();
			mouseHandle->resetALLKeysStates();

			if (sceneName == "Reward")
			{
				scenes[sceneName]->point = activeScene->point;
				scenes[sceneName]->playingtime = activeScene->playingtime;
			}
				

			activeScene = scenes[sceneName];
			//pickerHandle->setActiveCam(activeScene->getWorld()->renderCam);
			SphereColliderC::frustumHandle = ComponentsPool::cameraComponent->frustum;
			activeScene->getWorld()->dirlight->updatedFlag = true;
		}

		else
		{
			printf("%s is invalid", sceneName.c_str());
		}
	}

	void SceneManager::debugMeshLuaRegister(void)
	{
		// debug mesh properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "DebugMesh");
		lua_newtable(S);

		lua_pushstring(S, "Sphere");
		luaHandle->pushLUA_DebugMeshSphereEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "AABB");
		luaHandle->pushLUA_DebugMeshAABBEnableCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void SceneManager::LensFlareGSLuaRegister(void)
	{
		// lensflare properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "LensFlare");
		lua_newtable(S);

		lua_pushstring(S, "Enable");
		luaHandle->pushLUA_LFEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Scale");
		luaHandle->pushLUA_LFScaleCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Bias");
		luaHandle->pushLUA_LFBiasCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Distortion");
		luaHandle->pushLUA_LFDistortionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Ghost");
		luaHandle->pushLUA_LFGhostCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "GhostDisperal");
		luaHandle->pushLUA_LFGhostDispersalCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "HaloWidth");
		luaHandle->pushLUA_LFHaloWidthCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void SceneManager::FXAAGSLuaRegister(void)
	{
		// FXAA properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "FXAA");
		lua_newtable(S);

		lua_pushstring(S, "Enable");
		luaHandle->pushLUA_FXAAEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Size");
		luaHandle->pushLUA_FXAASizeCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void SceneManager::BloomGSLuaRegister(void)
	{
		// bloom properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "Bloom");
		lua_newtable(S);

		lua_pushstring(S, "Enable");
		luaHandle->pushLUA_BloomEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "BlurRadius");
		luaHandle->pushLUA_BloomRadiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "BlurSize");
		luaHandle->pushLUA_BloomSizeCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void SceneManager::SSAOGSLuaRegister(void)
	{
		// ssao properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "SSAO");
		lua_newtable(S);

		lua_pushstring(S, "Enable");
		luaHandle->pushLUA_SSAOEnableCB(S); // register liao
		lua_settable(S, -3);

		lua_pushstring(S, "KernelSize");
		luaHandle->pushLUA_SSAOKernelSizeCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Radius");
		luaHandle->pushLUA_SSAORadiusCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Strength");
		luaHandle->pushLUA_SSAOStrengthCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void SceneManager::MotionBlurGSLuaRegister(void)
	{
		// Motionblur properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "MotionBlur");
		lua_newtable(S);

		lua_pushstring(S, "Enable");
		luaHandle->pushLUA_MBEnableCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "MaxSample");
		luaHandle->pushLUA_MBMaxSampleCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Scale");
		luaHandle->pushLUA_MBScaleCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------


		// reso properties
		//----------------------------------------------------------------------------------------
		// multidimensional table
		lua_pushstring(S, "Resolution");
		lua_newtable(S);

		lua_pushstring(S, "Scene");
		luaHandle->pushLUA_getSceneResolutionCB(S);
		lua_settable(S, -3);

		lua_pushstring(S, "Shadow");
		luaHandle->pushLUA_getShadowResolutionCB(S);
		lua_settable(S, -3);

		lua_settable(S, -3);
		//----------------------------------------------------------------------------------------
	}

	void SceneManager::destroyAllScenes(void)
	{
		for (auto &x : scenes)
		{
			x.second->Destroy();
			delete x.second;
		}

		scenes.clear();
		activeScene = nullptr;
	}

	void SceneManager::RestartScene(const string & s)
	{
		scenes[s]->restartFlag = true;
	}

	void SceneManager::terminate(void)
	{
		destroyAllScenes();

		if (S != nullptr)
		{
			lua_close(S);
			S = nullptr;
		}

		luaHandle = nullptr;

		if (goption)
		{
			// save the goption before closing
			string filename = "Content//assets//GraphicsOption.lua";

			// remove the existing file 
			remove(filename.c_str());

			// automatically create new file again
			std::ofstream outputFile;
			outputFile.open(filename);
			outputFile << *goption;
			outputFile.close();

			delete goption;
			goption = nullptr;
		}
	}



	///////////////////////////////////////////////////////////////////////
	// ALL CB Funtions below ********************************************//
	//*******************************************************************//
	//*******************************************************************//
	//*******************************************************************//
	///////////////////////////////////////////////////////////////////////

	static bool shiftpress = false;
	static bool typingmode = false;
	static bool capslock = false;
	static unsigned int maxlength = 70;

	void SceneManager::KeyboardCB(const KEY& Key, const KEY_STATE& action)
	{
		if (!typingmode) keyboardHandle->updateKey(Key, action);
		
		if (Key == KEY_LSHIFT || Key == KEY_RSHIFT)
		{
			if (action == KEY_STATE_PRESS || action == KEY_STATE_REPEAT)
			{
				shiftpress = true;
			}
			else
			{
				shiftpress = false;
			}
		}
		
	}

	void SceneManager::TYPE_NormalKeyCB(const KEY& Key)
	{
		std::string &str = guiHandle->typestr;

		if (Key == KEY_BACKSPACE)
		{
			if (str.length() > 1)
			{
				str.pop_back();
			}
		}
		
		if (typingmode == true && str.length() < maxlength)
		{
			char k = Key;

			// accept A to Z letters
			if (Key >= KEY_A && Key <= KEY_Z)
			{
				// convert char based on caps lock
				if (!capslock)
				{
					k += 32;
				}

				if (shiftpress)
				{
					if (!capslock)
					{
						k -= 32;
					}
					else
					{
						k += 32;
					}

				}

				str += k;
			}

			else if (Key == KEY_SPACE)
			{
				str += Key;
			}

			else if (Key >= KEY_COMMA && Key <= KEY_SLASH)
			{
				if (shiftpress)
				{
					if (Key >= KEY_PERIOD)
					{
						k += 16;
					}
					else
					{
						k = KEY_LESSTHAN;
					}
				}

				str += k;
			}

			else if (Key >= KEY_0 && Key <= KEY_9)
			{
				if (shiftpress)
				{
					switch(Key)
					{
					case KEY_9:
						k = KEY_LEFTBRACKET;
						break;
					case KEY_0:
						k = KEY_RIGHTBRACKET;
						break;
					case KEY_2:
						k = KEY_AT;
						break;
					case KEY_6:
						k = KEY_SQUARE;
						break;
					case KEY_7:
						k = KEY_ANDSIGN;
						break;
					case KEY_8:
						k = KEY_TIMES;
						break;
					default:
						k -= 16;
						break;
					}
				}

				str += k;
			}

			else if (Key >= KEY_LEFT_BRACKET && Key <= KEY_RIGHT_BRACKET)
			{
				if (shiftpress)
				{
					if (Key >= KEY_PERIOD)
					{
						k += 32; 
					}
				}

				str += k;
			}
			
			else if (Key == KEY_APOSTROPHE)
			{
				if (shiftpress)
				{
					k = KEY_DOUBLEAPOSTROPHE;
				}
				str += k;
			}

			else if (Key == KEY_EQUAL)
			{
				if (shiftpress)
				{
					k = KEY_PLUS;
				}
				str += k;
			}

			else if (Key == KEY_SEMICOLONCOMMA)
			{
				if (shiftpress)
				{
					k = KEY_SEMICOLON;
				}
				str += k;
			}
		}
	}

	void SceneManager::MouseCursorCB(const double& x, const double& y)
	{
		// mouse cursor check
		mouseHandle->setMousePos(static_cast<float>(x), static_cast<float>(y));
	}

	void SceneManager::MouseButtCB(const KEY& Key, const KEY_STATE& action)
	{
		// mouse butt press check
		mouseHandle->updateKeyPressed((MOUSE)Key, action);
	}

	void SceneManager::MouseCursorEnterCB(const bool& enter)
	{
		// check whether the cursor is inside the bound or not
		mouseHandle->setInBound(enter);
	}

	void SceneManager::MouseScrollCB(const double& xoffset, const double& yoffset)
	{
		// mouse scrolling check
		mouseHandle->setScrolling(-static_cast<float>(yoffset));
	}

	void SceneManager::WindowResizeCB(const int& width, const int& height)
	{
		// check whether user got resize the monitor or not
		// always update the window width and height
		windowHandle->setWidthAndHeight(width, height);

		for (auto &x : scenes)
		{
			x.second->WindowResizeCB(1280, 720);
		}
	}

	void SceneManager::WindowPosCB(const int& x, const int& y)
	{
		// window current pos
		windowHandle->setWindowPosXAndY(x, y);
		activeScene->WindowPosCB(x, y);
	}

	void SceneManager::WindowIconifiyCB(const int& i)
	{
		// window minimise or not
		activeScene->WindowIconifiyCB(i);
	}

	void SceneManager::WindowShldCloseCB(const int& i)
	{
		exit = true;
	}

	int SceneManager::LUA_setWindowSizeCB(lua_State * L)
	{
		int wx = 0, wy = 0;

		wx = (int)lua_tonumber(S, 1);
		wy = (int)lua_tonumber(S, 2);

		glfwSetWindowSize(windowHandle->m_window, wx, wy);

		WindowResizeCB(wx, wy);

		return 0;
	}

	int SceneManager::LUA_setWindowFullScreenCB(lua_State * L)
	{
		bool fullscreen = false;
		if ((int)lua_tonumber(S, 1) > 0)
		{
			fullscreen = true;
		}

		// change to fullscreen pls

		return 0;
	}

	int SceneManager::LUA_setCursorEnableCB(lua_State * L)
	{
		if(itob(lua_toboolean(L, 1)) == true)
			glfwSetInputMode(windowHandle->m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(windowHandle->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return 0;
	}

	int SceneManager::LUA_createSceneCB(lua_State * L)
	{
		string scenename, worldpath;

		scenename = lua_tostring(S, 1);
		worldpath = lua_tostring(S, 2);

		addScene(scenename, worldpath);

		// make sure that the call back is still on this manager
		luaHandle->setCallBack(this);

		return 0;
	}

	int SceneManager::LUA_setActiveSceneCB(lua_State * L)
	{
		string scenename;

		scenename = lua_tostring(S, 1);

		changeScene(scenename);

		return 0;
	}

	int SceneManager::LUA_SaveSceneCB(lua_State * L)
	{
		activeScene->Save();
		return 0;
	}

	int SceneManager::LUA_LoadSceneCB(lua_State * L)
	{
		activeScene->Restart();
		return 0;
	}

	

	int SceneManager::LUA_DebugMeshSphereEnableCB(lua_State * L)
	{
		goption->setDebugMeshRenderSphere(itob(lua_toboolean(L, 1)));
		return 0;
	}

	int SceneManager::LUA_DebugMeshAABBEnableCB(lua_State * L)
	{
		goption->setDebugMeshRenderAABB(itob(lua_toboolean(L, 1)));
		return 0;
	}

	int SceneManager::LUA_SSAOEnableCB(lua_State * L)
	{
		goption->setssaoEnable(itob(lua_toboolean(L, 1)));
		return 0;
	}

	int SceneManager::LUA_SSAOKernelSizeCB(lua_State * L)
	{
		goption->setssaoKernel((int)lua_tointeger(L, 1));
		return 0;
	}

	int SceneManager::LUA_SSAORadiusCB(lua_State * L)
	{
		goption->setssaoRadius((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_SSAOStrengthCB(lua_State * L)
	{
		goption->setssaoStrength((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_MBEnableCB(lua_State * L)
	{
		goption->setmotionBlurEnable(itob(lua_toboolean(L, 1)));
		return 0;
	}

	int SceneManager::LUA_MBMaxSampleCB(lua_State * L)
	{
		goption->setmotionblur_maxsample((int)lua_tointeger(S, 1));
		return 0;
	}

	int SceneManager::LUA_MBScaleCB(lua_State * L)
	{
		goption->setmotionblur_framerate((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_BloomEnableCB(lua_State * L)
	{
		bool v = false;
		if (lua_toboolean(S, 1) == 1)
		{
			v = true;
		}
		goption->setbloomEnable(v);
		return 0;
	}

	int SceneManager::LUA_BloomRadiusCB(lua_State * L)
	{
		goption->setblurRadius((int)lua_tointeger(S, 1));
		return 0;
	}

	int SceneManager::LUA_BloomSizeCB(lua_State * L)
	{
		goption->setblurSize((int)lua_tointeger(S, 1));
		return 0;
	}

	int SceneManager::LUA_FXAAEnableCB(lua_State * L)
	{
		bool v = false;
		if (lua_toboolean(S, 1) == 1)
		{
			v = true;
		}
		goption->setfxaa_enable(v);
		return 0;
	}

	int SceneManager::LUA_FXAASizeCB(lua_State * L)
	{
		goption->setfxaa_Size((int)lua_tointeger(S, 1));
		return 0;
	}

	int SceneManager::LUA_LFEnableCB(lua_State * L)
	{
		bool v = false;
		if (lua_toboolean(S, 1) == 1)
		{
			v = true;
		}
		goption->setlensFEnable(v);
		return 0;
	}

	int SceneManager::LUA_LFScaleCB(lua_State * L)
	{
		goption->setlensFScale((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_LFBiasCB(lua_State * L)
	{
		goption->setlensFBias((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_LFDistortionCB(lua_State * L)
	{
		goption->setlensFDistortion((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_LFGhostCB(lua_State * L)
	{
		goption->setlensFGhost((int)lua_tointeger(S, 1));
		return 0;
	}

	int SceneManager::LUA_LFGhostDispersalCB(lua_State * L)
	{
		goption->setlensFGhostDispersal((float)lua_tonumber(S, 1));
		return 0;
	}

	int SceneManager::LUA_LFHaloWidthCB(lua_State * L)
	{
		goption->setlensFHaloWidth((float)lua_tonumber(S, 1));
		return 0;
	}
	int SceneManager::LUA_getSceneResolutionCB(lua_State * L)
	{
		goption->setResolution(vec2i((int)lua_tonumber(S, 1), (int)lua_tonumber(S, 2)));
		return 0;
	}
	int SceneManager::LUA_getShadowResolutionCB(lua_State * L)
	{
		goption->setShadowResolution(vec2i((int)lua_tonumber(S, 1), (int)lua_tonumber(S, 2)));
		return 0;
	}
}
