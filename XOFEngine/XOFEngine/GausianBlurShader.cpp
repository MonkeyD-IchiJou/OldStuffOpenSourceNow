#include "GausianBlurShader.h"

namespace pp
{
	GausianBlurShader::GausianBlurShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//Gausian1DShader.fragmentshader")
	{
		getAllUniformLocations();
	}


	GausianBlurShader::~GausianBlurShader(void)
	{

	}

	void GausianBlurShader::load_TexUnit(int i)
	{
		loadU_1i(m_parameters["U_TEXUNIT"], i);
	}

	void GausianBlurShader::load_BlurRadius(int i)
	{
		loadU_1i(m_parameters["U_BLURRADIUS"], i);
	}

	void GausianBlurShader::load_BlurSigma(float g)
	{
		loadU_1f(m_parameters["U_SIGMA"], g);
	}

	void GausianBlurShader::load_BlurDirection(float x, float y)
	{
		loadU_Vec2f(m_parameters["U_BDIRECTION"], x, y);
	}

	void GausianBlurShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEXUNIT"] = getUniformLocation("uInputTex");

		m_parameters["U_BLURRADIUS"] = getUniformLocation("uBlurRadius");
		m_parameters["U_SIGMA"] = getUniformLocation("uBlurSigma");  // never use?
		m_parameters["U_BDIRECTION"] = getUniformLocation("uBlurDirection");
	}
}
