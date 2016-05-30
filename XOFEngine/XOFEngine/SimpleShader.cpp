#include "SimpleShader.h"

namespace pp
{

	SimpleShader::SimpleShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//simpleShader.fragmentshader")
	{
		getAllUniformLocations();
	}

	SimpleShader::~SimpleShader(void)
	{
	}

	void SimpleShader::load_TexUnit(int i)
	{
		loadU_1i(m_parameters["U_TEX"], i);
	}

	void SimpleShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEX"] = getUniformLocation("tex");
	}

	
	
}

