#include "GameApplication.h"

using namespace pp;

int main(void)
{
	// game loop
	GameApplication* gameapp = new GameApplication();
	gameapp->setUp();
	gameapp->run();

	gameapp->terminate();
	delete gameapp;
	gameapp = nullptr;

	return 0;
}