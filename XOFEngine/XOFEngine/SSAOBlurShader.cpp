#include "SSAOBlurShader.h"


namespace pp
{
	SSAOBlurShader::SSAOBlurShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//ssaoBlur.fragmentshader")
	{
		getAllUniformLocations();
	}


	SSAOBlurShader::~SSAOBlurShader()
	{
	}

	void SSAOBlurShader::getAllUniformLocations(void)
	{
		m_parameters["U_SSAO"] = getUniformLocation("ssaoInput");
	}

	void SSAOBlurShader::load_SSAOTexUnit(int i)
	{
		loadU_1i(m_parameters["U_SSAO"], i);
	}
	
}
