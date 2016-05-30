#ifndef DIR_LIGHT_SHADER_H
#define DIR_LIGHT_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;


namespace pp
{
	class DirLightC;
	class PointLightC;

	class LightShader :
		public ShaderProgram
	{
	public:
		LightShader(void);
		~LightShader(void);

		void load_ALLGPASS(const int& position, const int& normal, const int& diffuse, const int& ssao);
		
		void load_DirLight(const DirLightC& light);

		void load_PointLight(const PointLightC& light);

		void load_ViewPos(const vec3f& v);

		void load_SSAOEnable(const int& i);

		void load_LightType(const int& type);

		void load_ModelMatrix(const mat4f & m);

		void load_ScreenSize(const float& x, const float& y);

		void load_SkyboxUnit(const int & i);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

