#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H


namespace pp
{
	class GLFW_Window;
	class SceneManager;

	class GameApplication
	{
	public:
		GameApplication(void);
		~GameApplication(void);

		// set up everything that are needed to run the engine or game
		void setUp(void);

		// run the game scene, update and render everyframe
		void run(void);

		// terminate the whole program ( delete everything pls )
		void terminate(void);

		

	private:
		void glewSetUp(void);

		GLFW_Window* windowHandle;
		SceneManager* scenemanagerHandle; // all the bloody scenes is here
	};

}

#endif

