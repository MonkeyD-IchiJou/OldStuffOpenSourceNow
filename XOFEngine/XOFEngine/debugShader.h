#ifndef DEBUG_SHADER_H
#define DEBUG_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;


namespace pp
{
	class debugShader :
		public ShaderProgram
	{
	public:
		debugShader(void);
		~debugShader(void);
		void load_color(const vec3f &color);
	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

