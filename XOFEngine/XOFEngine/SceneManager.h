#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "callbacks.h"
#include "LUACallbacks.h"
#include "App.h"
#include "enumc.h"

#include "MathsHeader.h"

#include <map>
using std::map;

namespace pp
{
	class GLFW_Window;
	class scenebase;
	class gl_backend;
	class lua_backend;
	class GUIrenderEngine;
	class MousePicker;
	class GraphicEngine;
	class GraphicScale;

	class Mouse;
	class Keyboard;

	class PlayerManager;

	class SceneManager : public ICallbacks, public App, public LUACallbacks
	{
	public:
		
		// setting up all the available scenes in this program
		void setUp(void);

		// run the current active scene
		void run(void);

		// add scene into out scenemanager
		void addScene(const string& sceneName, const string& worldPath);

		// change this scene into the active scene
		void changeScene(const string& sceneName);

		// destroy all the scenes
		void destroyAllScenes(void);

		// restart the scene
		void RestartScene(const string& s);

		// destroy all the scene and reset everything
		void terminate(void);

		int LUA_setCursorEnableCB(lua_State* L) override;

		static scenebase* activeScene;
		GraphicScale* goption;
		string WhichScene;

		// Singleton class implementation
		static inline SceneManager* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new SceneManager();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		SceneManager(void);
		~SceneManager(void);
		void InputUpdate(void);

		/* ALL callback functions*/

		void KeyboardCB(const KEY& Key, const KEY_STATE& action) override;
		void TYPE_NormalKeyCB(const KEY& Key) override;
		void MouseCursorCB(const double& x, const double& y) override;
		void MouseButtCB(const KEY& Key, const KEY_STATE& action) override;
		void MouseCursorEnterCB(const bool& enter) override;
		void MouseScrollCB(const double& xoffset, const double& yoffset) override;
		void WindowResizeCB(const int& width, const int& height) override;
		void WindowPosCB(const int& x, const int& y) override;
		void WindowIconifiyCB(const int& i) override;
		void WindowShldCloseCB(const int& i) override;


		/* ALL Lua Related Functions */
		
		void luaSetUp(void);
		void luaRegistration(void);

		/* all lua registration helpers */

		void debugMeshLuaRegister(void);
		void LensFlareGSLuaRegister(void);
		void FXAAGSLuaRegister(void);
		void BloomGSLuaRegister(void);
		void SSAOGSLuaRegister(void);
		void MotionBlurGSLuaRegister(void);

		/* All lua callbacks functions here */

		/* window related */
		// from here --
		int LUA_setWindowSizeCB(lua_State* L) override;
		int LUA_setWindowFullScreenCB(lua_State* L) override;


		
		// till here --

		/* scene related */
		// from here --
		int LUA_createSceneCB(lua_State* L) override;
		int LUA_setActiveSceneCB(lua_State* L) override;
		int LUA_SaveSceneCB(lua_State* L) override;
		int LUA_LoadSceneCB(lua_State* L) override;
		// till here -- 

		/* graphics related */
		// from here --
		int LUA_DebugMeshSphereEnableCB(lua_State* L) override;
		int LUA_DebugMeshAABBEnableCB(lua_State* L) override;
		int LUA_SSAOEnableCB(lua_State* L) override;
		int LUA_SSAOKernelSizeCB(lua_State* L) override;
		int LUA_SSAORadiusCB(lua_State* L) override;
		int LUA_SSAOStrengthCB(lua_State* L) override;
		int LUA_MBEnableCB(lua_State* L) override;
		int LUA_MBMaxSampleCB(lua_State* L) override;
		int LUA_MBScaleCB(lua_State* L) override;
		int LUA_BloomEnableCB(lua_State* L) override;
		int LUA_BloomRadiusCB(lua_State* L) override;
		int LUA_BloomSizeCB(lua_State* L) override;
		int LUA_FXAAEnableCB(lua_State* L) override;
		int LUA_FXAASizeCB(lua_State* L) override;
		int LUA_LFEnableCB(lua_State* L) override;
		int LUA_LFScaleCB(lua_State* L) override;
		int LUA_LFBiasCB(lua_State* L) override;
		int LUA_LFDistortionCB(lua_State* L) override;
		int LUA_LFGhostCB(lua_State* L) override;
		int LUA_LFGhostDispersalCB(lua_State* L) override;
		int LUA_LFHaloWidthCB(lua_State* L) override;

		int LUA_getSceneResolutionCB(lua_State* L) override;
		int LUA_getShadowResolutionCB(lua_State* L) override;
		// till here --


	private:

		/* All variables */

		GLFW_Window* windowHandle;
		Mouse* mouseHandle;
		gl_backend* BackEndHandle;
		Keyboard* keyboardHandle;
		GUIrenderEngine* guiHandle;
		GraphicEngine* graphicsHandle;
		MousePicker* pickerHandle;

		map<std::string, scenebase*> scenes;
		

		lua_State* S;
		lua_backend* luaHandle;

		
		// graphics option for this scene
		void initGoption(void);

		PlayerManager* playerHandle;
		static SceneManager* s_instance;
		
	};
}

#endif
