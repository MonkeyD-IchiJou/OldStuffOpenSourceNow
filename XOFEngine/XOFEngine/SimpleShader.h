#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "ShaderProgram.h"
#include "mat4.h"
#include "vec4.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class SimpleShader :
		public ShaderProgram
	{
	public:
		SimpleShader(void);
		~SimpleShader(void);

		void load_TexUnit(int i);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}


#endif

