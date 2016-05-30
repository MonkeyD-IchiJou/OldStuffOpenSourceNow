#ifndef DIR_LIGHT_H
#define DIR_LIGHT_H

#include "LightC.h"
#include "mat4.h"

using namespace Math;

namespace pp
{
	class LightShader;
	class CameraC;
	class GeometryPassShader;

	class DirLightC :
		public LightC
	{
	public:
		DirLightC(void);
		virtual ~DirLightC(void);

		void update(const float& dt) override;
		void abstractclass(void) override;
		void save(ofstream& myFile, const unsigned int & guid) override;

		// the ortho projection
		void LightProjectionUpdate(void);

		// the light view (normally is following player de)
		void LightLookAtUpdate(const float& dt, const CameraC& cam);

		// change the light dir
		void changeLightDir(const vec3f &axisRotate, const float &angle);

		// get projection * view
		mat4f getLightSpace(void) const;

		// only difference is it got direction 
		vec3f lightdirection;

		inline void setLightProjSize(double &lightproj) { this->lightprojsize = lightproj; updatedFlag = true; }

		static double lightprojsize;
	private:
		static LightShader* shader;
		static GeometryPassShader* gshader;

		// light mat
		mat4f lightProjection, lightView;

		// for shadow looking at
		vec3f lightlookingtarget;

		// light up vector
		vec3f lightup;

		double near_plane, far_plane;
	};

}

#endif
