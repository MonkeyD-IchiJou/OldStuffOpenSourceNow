#ifndef GP_SHADER_H
#define GP_SHADER_H


#include "ShaderProgram.h"
#include <map>
#include <string>
#include <vector>

using std::vector;
using std::map;
using std::string;



namespace pp
{
	class GeometryPassShader :
		public ShaderProgram
	{
	public:
		GeometryPassShader(void);
		~GeometryPassShader(void);

		// basic mvp info
		void load_ModelMatrix(const mat4f &matrix);
		void load_PrevModelViewProjectionMatrix(const mat4f &matrix);

		void load_LightMatrix(const mat4f &mat);
		void load_DepthTex(const int & i);

		// materials info
		void load_Color(const vec3f& color);		// load color 
		void load_Shininess(const float& s);   // if shininess is 0 .. means no lighting
		void load_Emissive(const float & e);

		void load_LightDir(const vec3f & lightdir);


	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};

}

#endif

