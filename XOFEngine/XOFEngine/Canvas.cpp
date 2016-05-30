#include "Canvas.h"


namespace pp
{
	CanvasC::CanvasC() : Component(CANVAS)
	{
		for (int i = 0; i < AT_EASE; i++)
		{
			instruction[i] = false;
		}
	}


	CanvasC::~CanvasC()
	{
	}

	void CanvasC::update(const float & dt)
	{

	}

	void CanvasC::save(ofstream & myFile, const unsigned int & guid)
	{

	}
}
