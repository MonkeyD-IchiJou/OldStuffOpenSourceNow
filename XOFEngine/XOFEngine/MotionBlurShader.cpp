#include "MotionBlurShader.h"

namespace pp
{

	MotionBlurShader::MotionBlurShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//motionBlur.fragmentshader")
	{
		getAllUniformLocations();
	}


	MotionBlurShader::~MotionBlurShader(void)
	{

	}

	void MotionBlurShader::load_ALLTexUnit(const int& t, const int& v)
	{
		loadU_1i(m_parameters["U_TEXUNIT"], t);
		loadU_1i(m_parameters["U_VELOCITYUNIT"], v);
	}

	void MotionBlurShader::load_InputTex(const int & t)
	{
		loadU_1i(m_parameters["U_TEXUNIT"], t);
	}

	void MotionBlurShader::load_VelocityScale(const float& s)
	{
		loadU_1f(m_parameters["U_VELOCITYSCALE"], s);
	}

	void MotionBlurShader::load_MaxSample(const int& s)
	{
		loadU_1i(m_parameters["U_MAX_SAMPLES"], s);
	}

	void MotionBlurShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEXUNIT"] = getUniformLocation("uTexInput");
		m_parameters["U_VELOCITYUNIT"] = getUniformLocation("uTexVelocity");
		m_parameters["U_VELOCITYSCALE"] = getUniformLocation("uVelocityScale");
		m_parameters["U_MAX_SAMPLES"] = getUniformLocation("MAX_SAMPLES");
	}


}
