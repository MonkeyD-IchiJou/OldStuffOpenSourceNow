#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "callbacks.h"
#include "enumc.h"
#include "MathsHeader.h"

#include <string>
using std::string;

namespace pp
{
	class World;
	class GraphicEngine;
	class GLFW_Window;
	class lua_backend;

	class scenebase : public ICallbacks
	{
	public:
		scenebase(const std::string & sceneName, const std::string & worldPath);
		virtual ~scenebase(void);

		// scene initiation before update and render
		virtual bool Init(void) = 0;

		// scene update before render
		virtual void update(const float &dt) = 0;

		// scene render 
		virtual void render(void) = 0;

		// scene update after render
		virtual void lateupdate(const float &dt) = 0;

		// save all the entities current progress into lua save file 
		virtual void Save(void);

		// load the scene again with its current save file
		virtual void Restart(void) = 0;

		// set the scene name
		inline void setSceneName(const std::string & n) { this->sceneName = n; }

		// get the scene name
		inline std::string getSceneName(void) const { return this->sceneName; }

		// scene destroy 
		virtual void Destroy(void);

		// delete the scene and its save file 
		inline void deleteScene(void) const { remove(worldPath.c_str()); }

		// get the handle of the world (all entities) of this scene
		World* getWorld(void);

		bool restartFlag;

		int point;

		double playingtime;

		vec3f checkpoint;

	protected:
		World* world;
		GraphicEngine* graphicEngineer;
		std::string sceneName, worldPath;

		static GLFW_Window* windowHandle;
	};
}

#endif


