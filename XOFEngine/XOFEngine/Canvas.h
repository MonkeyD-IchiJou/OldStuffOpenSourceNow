#ifndef CANVAS_H_
#define CANVAS_H_
#include "Component.h"
#include <vector>
#include "enumc.h"

namespace pp
{
	class GUIText;

	class CanvasC :
		public Component
	{
	public:
		CanvasC();
		virtual ~CanvasC();

		// every components got its very own update methods
		void update(const float &dt) override;

		// every components are able to save themself 
		void save(ofstream& myFile, const unsigned int& guid) override;
		
		bool instruction[AT_EASE];

	};
}
#endif

