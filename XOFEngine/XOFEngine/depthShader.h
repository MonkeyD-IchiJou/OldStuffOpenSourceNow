#ifndef DEPTH_SHADER_H
#define DEPTH_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;


namespace pp
{
	class depthShader :
		public ShaderProgram
	{
	public:
		depthShader(void);
		~depthShader(void);

		void load_LightSpaceMatrix(const mat4f & m);
		void load_ModelMatrix(const mat4f & m);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

