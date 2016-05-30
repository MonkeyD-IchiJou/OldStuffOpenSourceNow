#ifndef FXAA_SHADER_H
#define FXAA_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;


namespace pp
{
	class FXAAShader :
		public ShaderProgram
	{
	public:
		FXAAShader(void);
		~FXAAShader(void);

		void load_TexUnit(const int& i);
		void load_FrameBufferSize(const float& x, const float& y);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

