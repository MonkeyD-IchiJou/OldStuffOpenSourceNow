#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "LightC.h"

#include "mat4.h"
using namespace Math;

namespace pp
{
	class NullShader;
	class LightShader;
	class SphereColliderC;

	class PointLightC :
		public LightC
	{
	public:
		PointLightC(void);
		virtual ~PointLightC(void);

		void update(const float& dt) override;
		void abstractclass(void) override;
		void save(ofstream& myFile, const unsigned int & guid) override;

		void ShaderReadInfo(const bool & pon) const;

	private:
		// every renderer must have its own frustum sphere radius
		SphereColliderC* spherecollider;

		static NullShader* nullshader;
		static LightShader* pntlightshader;
		float CalcPointLightBSphere(void) const;

		mat4f *translationMat4;
		mat4f lightvolumescale;

		
	};
}

#endif

