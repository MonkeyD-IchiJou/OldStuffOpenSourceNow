#include "GameApplication.h"
#include "MyMath.h"

#include <GL\glew.h>
#include "SceneManager.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "ModelLibrary.h"
#include "TextureLibrary.h"
#include "FontsLibrary.h"

#include "ShaderHeaven.h"

#include "GraphicEngine.h"
#include "GUIrenderEngine.h"

#include "GLFW_Window.h"

#include "PlayerManager.h"

namespace pp
{

	GameApplication::GameApplication(void) :
		windowHandle(nullptr),
		scenemanagerHandle(nullptr)
	{
		Math::InitRNG();
	}

	GameApplication::~GameApplication(void)
	{
		terminate();
	}

	void GameApplication::setUp(void)
	{
		// prevent memory leak
		terminate();

		// window creation here
		windowHandle = GLFW_Window::getInstance();
		windowHandle->setUp();

		// glew setting
		glewSetUp();

		// init inputs
		Keyboard::getInstance()->resetAllKeys();
		Mouse::getInstance()->resetALLKeysStates();

		// init all the model
		ModelLibrary::getInstance()->init();

		// init all the texturelibrary
		TextureLibrary::getInstance()->init();

		// init all fonts
		FontsLibrary::getInstance()->initAllFonts();

		// init all the shaders
		ShaderHeaven::getInstance()->start();

		PlayerManager::getInstance()->CreatePlayer();

		// set up all the scenes in scenemanager
		scenemanagerHandle = SceneManager::getInstance();
		scenemanagerHandle->setUp();

		// Define the viewport dimensions
		glViewport(0, 0, windowHandle->getWindowWidth(), windowHandle->getWindowHeight());
	}


	void GameApplication::run(void)
	{
		// nothing first
		scenemanagerHandle->run();
	}


	void GameApplication::terminate(void)
	{
		if (windowHandle != nullptr)
		{
			windowHandle->destroyWindow();
			windowHandle = nullptr;
		}

		if (scenemanagerHandle != nullptr) 
		{
			scenemanagerHandle->terminate();
			scenemanagerHandle = nullptr;
		}
	}


	void GameApplication::glewSetUp(void)
	{
		// glew set up
		glewExperimental = true; // Needed for core profile

		//Initialize GLEW
		GLenum err = glewInit();

		//If GLEW hasn't initialized
		if (err != GLEW_OK)
		{
			printf("Error: %s\n", glewGetErrorString(err));
		}
	}
}
