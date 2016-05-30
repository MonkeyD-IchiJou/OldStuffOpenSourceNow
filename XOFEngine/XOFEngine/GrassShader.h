#ifndef GRASS_SHADER_H
#define GRASS_SHADER_H

#include "ShaderProgram.h"
#include "mat4.h"
#include "vec4.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class GrassShader :
		public ShaderProgram
	{
	public:
		GrassShader(void);
		~GrassShader(void);

		void load_ModelMatrix(const mat4f& m);
		void load_Timer(const float & timer);
		void load_WindDir(const vec3f& wd);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}


#endif

