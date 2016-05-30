#ifndef PPPAS_SHADER_H
#define PPPAS_SHADER_H

#include "ShaderProgram.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class PostProcessPassShader :
		public ShaderProgram
	{
	public:
		PostProcessPassShader(void);
		~PostProcessPassShader(void);

		void load_TextureUnit(int i);
		void load_BiasAndScale(float bias, float scale);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}


#endif

