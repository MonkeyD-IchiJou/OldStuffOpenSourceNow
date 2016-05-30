#ifndef MOTION_BLUR_SHADER_H
#define MOTION_BLUR_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class MotionBlurShader :
		public ShaderProgram
	{
	public:
		MotionBlurShader(void);
		virtual ~MotionBlurShader(void);

		void load_ALLTexUnit(const int& t, const int& v);
		void load_InputTex(const int & t);
		void load_VelocityScale(const float& s);
		void load_MaxSample(const int& s);

	private:
		map<string, unsigned int> m_parameters;

	protected:
		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

