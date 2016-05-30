#include "Scene3D.h"
#include "World.h"
#include "graphicEngine.h"
#include "GLFW_Window.h"

#include "lua\lua.hpp"
#include "lua_backend.h"

#include "GUIrenderEngine.h"

#include "PlayerManager.h"
#include "Entity.h"

namespace pp
{
	Scene3D::Scene3D(const std::string & sceneName, const std::string & worldPath) : 
		scenebase(sceneName, worldPath),
		guiHandle(nullptr),
		totalPlayingTime(0.f),
		totalDieingNumber(0)
	{
		guiHandle = GUIrenderEngine::getInstance();
		checkPoint.Set(0, 1.f, 0);
	}

	Scene3D::~Scene3D(void)
	{
		Destroy();
	}

	bool Scene3D::Init(void)
	{
		// prevent memory leak
		Destroy();

		// first create the world for this scene
		world = new World(worldPath, this->sceneName);
		world->create();
		
		// get the handle of the graphic engine
		graphicEngineer = GraphicEngine::getInstance();
		
		return true;
	}

	void Scene3D::update(const float & dt)
	{
		playingtime += (double)dt;

		if (restartFlag == true)
		{
			Restart();
			restartFlag = false;
		}
		// components all update inside the world at one go
		world->update(dt);

		// graphic neccessary update stuff before rendering
		graphicEngineer->update(dt);
		guiHandle->Update(dt);
	}

	void Scene3D::render(void)
	{
		World &w = *world;
		graphicEngineer->render(w);
		guiHandle->renderGUI(w);
	}

	void Scene3D::lateupdate(const float &dt)
	{
		// update prev MVP to all the entity
		world->lateupdate(dt);
	}

	void Scene3D::Restart(void)
	{
		if (world)
		{
			world->destroy();
			delete world;
			world = nullptr;
		}

		point = 0;
		playingtime = 0;

		// delete the previous world and restart a new one
		world = new World(worldPath, this->sceneName);
		world->create();

		PlayerManager::getInstance()->Restart();
	}

	/*********************************************************************/
	// ALL CB And HELPER Funtions below **********************************/
	/*********************************************************************/
	/*********************************************************************/
	/*********************************************************************/
	/*********************************************************************/

	void Scene3D::WindowResizeCB(const int& width, const int& height)
	{
		// check whether user got resize the monitor or not
		// always update the window width and height
		world->updateALLCamAspect(static_cast<double>(width) / static_cast<double>(height));
	}

	void Scene3D::WindowIconifiyCB(const int& i)
	{
		// window minimise or not
	}
}







