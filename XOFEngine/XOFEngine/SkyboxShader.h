#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include "ShaderProgram.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class SkyboxShader :
		public ShaderProgram
	{
	public:
		SkyboxShader(void);
		~SkyboxShader(void);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}


#endif

