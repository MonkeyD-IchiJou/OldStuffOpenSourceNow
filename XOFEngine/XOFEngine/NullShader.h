#ifndef NULL_SHADER_H
#define NULL_SHADER_H

#include "ShaderProgram.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class NullShader :
		public ShaderProgram
	{
	public:
		NullShader(void);
		~NullShader(void);

		void load_ModelMatrix(mat4f &matrix);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};

}

#endif

