#include "LightC.h"


namespace pp
{
	LightC::LightC(LIGHTTYPE type) : 
		Component(LIGHT),
		type(type)
	{
	}

	LightC::~LightC(void)
	{
	}

	void LightC::update(const float& dt)
	{
		// nothing to update dude
	}

	void LightC::save(ofstream & myFile, const unsigned int & guid)
	{
	}
}
