#include "PostProcessPassShader.h"

namespace pp
{

	PostProcessPassShader::PostProcessPassShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//PostProcessPass.fragmentshader")
	{
		getAllUniformLocations();
	}

	PostProcessPassShader::~PostProcessPassShader(void)
	{
	}

	void PostProcessPassShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEXTUREUNIT"] = getUniformLocation("texUnit");

		m_parameters["U_BIAS"] = getUniformLocation("uBias");
		m_parameters["U_SALE"] = getUniformLocation("uScale");

	}

	void PostProcessPassShader::load_TextureUnit(int i)
	{
		loadU_1i(m_parameters["U_TEXTUREUNIT"], i);
	}
	
	void PostProcessPassShader::load_BiasAndScale(float bias, float scale)
	{
		loadU_1f(m_parameters["U_BIAS"], bias); 
		loadU_1f(m_parameters["U_SALE"], scale);
	}
}

