#ifndef LIGHTC_H
#define LIGHTC_H

#include "Component.h"
#include "vec3.h"
using namespace Math;

namespace pp
{

	enum LIGHTTYPE
	{
		directionalLight = 0,
		pointLight,
		flashLight,
		noLight
	};

	class LightC :
		public Component
	{
	public:
		LightC(LIGHTTYPE type);
		virtual ~LightC(void);

		virtual void update(const float& dt) override;
		virtual void abstractclass(void) = 0;
		virtual void save(ofstream& myFile, const unsigned int & guid) override;

		vec3f lightPos, lightColor, ambient, diffuse, specular;
		LIGHTTYPE type;
	};

}

#endif

