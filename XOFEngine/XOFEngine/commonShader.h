#ifndef COMMON_SHADER_H
#define COMMON_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;


namespace pp
{
	class commonShader :
		public ShaderProgram
	{
	public:
		commonShader(void);
		~commonShader(void);

		void load_ModelMatrix(const mat4f & m);
		void load_color(const vec3f &color);
	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

