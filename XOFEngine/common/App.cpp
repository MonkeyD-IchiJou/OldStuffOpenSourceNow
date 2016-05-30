#include "App.h"

namespace pp
{
	App::App(void) : timer(new StopWatch()), FPS(0), frameTime(1000.0 / 60.0), exit(false), iconify(false), fullscreen(false), startedTimer(false)
	{

	}


	App::~App(void)
	{
		if (timer != NULL)
		{
			delete timer;
			timer = NULL;
		}
	}


	void App::calcFPS(void)
	{
		deltaTime = static_cast<float>(timer->getElapsedTime());

		if (deltaTime > 1.0f)
		{
			deltaTime = 0.01f;
		}

		FPS = 1 / deltaTime;
	}


	void App::startTimer(void)
	{
		if (!startedTimer)
		{
			timer->startTimer();
			startedTimer = true;
		}

	}


	void App::TimerShldWait(void)
	{
		timer->waitUntil(frameTime);
	}
}
