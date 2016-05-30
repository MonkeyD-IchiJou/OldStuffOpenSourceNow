#include "FXAAShader.h"


namespace pp
{
	FXAAShader::FXAAShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//FXAA.fragmentshader")
	{
		getAllUniformLocations();
	}


	FXAAShader::~FXAAShader(void)
	{
	}

	void FXAAShader::load_TexUnit(const int& i)
	{
		loadU_1i(m_parameters["U_TEX"], i);
	}

	void FXAAShader::load_FrameBufferSize(const float& x, const float& y)
	{
		loadU_Vec2f(m_parameters["U_FBOSIZE"], x, y);
	}

	void FXAAShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEX"] = getUniformLocation("buf0");
		m_parameters["U_FBOSIZE"] = getUniformLocation("frameBufSize");
	}
}