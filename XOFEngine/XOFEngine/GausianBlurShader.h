#ifndef GAUSIAN_BLUR_SHADER_H
#define GAUSIAN_BLUR_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class GausianBlurShader :
		public ShaderProgram
	{
	public:
		GausianBlurShader(void);
		virtual ~GausianBlurShader(void);

		void load_TexUnit(int i);
		void load_BlurRadius(int i);
		void load_BlurSigma(float g);
		void load_BlurDirection(float x, float y);

	private:
		map<string, unsigned int> m_parameters;

	protected:
		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif
