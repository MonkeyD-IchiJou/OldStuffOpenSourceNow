#include "depthShader.h"


namespace pp
{
	depthShader::depthShader(void) : ShaderProgram("Content//shader//depthShader.vertexshader", "Content//shader//depthShader.fragmentshader")
	{
		getAllUniformLocations();
	}


	depthShader::~depthShader(void)
	{
	}

	void depthShader::load_LightSpaceMatrix(const mat4f & m)
	{
		loadU_Mat4f(m_parameters["U_LIGHTSPACE"], m);
	}

	void depthShader::load_ModelMatrix(const mat4f & m)
	{
		loadU_Mat4f(m_parameters["U_MODEL"], m);
	}


	void depthShader::getAllUniformLocations(void)
	{
		m_parameters["U_LIGHTSPACE"] = getUniformLocation("lightSpaceMatrix");
		m_parameters["U_MODEL"] = getUniformLocation("model");
	}
}