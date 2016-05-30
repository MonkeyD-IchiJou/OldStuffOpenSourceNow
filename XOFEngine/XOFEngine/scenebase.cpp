#include "scenebase.h"

#include "GLFW_Window.h"

#include <fstream>

#include "engine_common.h"

#include "World.h"

namespace pp
{
	GLFW_Window* scenebase::windowHandle = nullptr;

	scenebase::scenebase(const std::string & sceneName, const std::string & worldPath) :
		world(nullptr),
		sceneName(sceneName),
		graphicEngineer(nullptr),
		worldPath(worldPath),
		restartFlag(false),
		point(0),
		playingtime(0.0)
	{
		if (windowHandle == nullptr) windowHandle = GLFW_Window::getInstance();
	}

	scenebase::~scenebase(void)
	{
		Destroy();
	}

	void scenebase::Save(void)
	{
		// now save all the entities
		world->save(); // save before destroy
	}

	World * scenebase::getWorld(void)
	{
		return this->world;
	}

	void scenebase::Destroy(void)
	{
		if (world)
		{
			world->destroy();
			delete world;
			world = nullptr;
		}
	}
}