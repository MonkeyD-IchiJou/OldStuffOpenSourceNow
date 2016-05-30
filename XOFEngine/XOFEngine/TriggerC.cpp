#include "TriggerC.h"

#include "Entity.h"

namespace pp
{
	TriggerC::TriggerC(void) :
		Component(TRIGGER)
	{
	}


	TriggerC::~TriggerC(void)
	{
	}

	void TriggerC::update(const float& dt)
	{
		/*if (updatedFlag && getOwner()->isActive())
		{

			updatedFlag = false;
		}*/
	}

	void TriggerC::save(ofstream& myFile, const unsigned int & guid)
	{

	}
}
