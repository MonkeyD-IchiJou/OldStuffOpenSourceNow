#ifndef APP_H
#define APP_H

#include "timer.h"

namespace pp
{
	class App
	{
	public:
		App(void);
		virtual ~App(void);

		void calcFPS(void);
		void startTimer(void);
		void TimerShldWait(void);

		bool exit;

	protected:
		float deltaTime;
		float FPS; // FPS of this game
		double frameTime; // time for each frame
		bool iconify, fullscreen;

	private:
		StopWatch *timer;
		bool startedTimer;

	};
}

#endif

