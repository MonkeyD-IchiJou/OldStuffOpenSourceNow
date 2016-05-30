#ifndef TRIGGERC_H
#define TRIGGERC_H

#include "Component.h"
#include <vector>
namespace pp
{

	class TriggerC :
		public Component
	{
	public:
		TriggerC(void);
		virtual ~TriggerC(void);

		void update(const float& dt) override;
		void save(ofstream& myFile, const unsigned int & guid) override;

		// total number of sharing == total number of alert
		std::vector<bool> alerts;
	};

}

#endif

