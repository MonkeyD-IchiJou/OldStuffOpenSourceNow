#include "NullShader.h"


namespace pp
{
	NullShader::NullShader(void) : ShaderProgram("Content//shader//nullshader.vertexshader", "Content//shader//nullshader.fragmentshader")
	{
		getAllUniformLocations();
	}


	NullShader::~NullShader(void)
	{
	}

	void NullShader::getAllUniformLocations(void)
	{
		m_parameters["U_MODEL"] = getUniformLocation("Model");

		// view and projection
		UniformBlockBinding("Matrices", 0);
	}

	void NullShader::load_ModelMatrix(mat4f & matrix)
	{
		loadU_Mat4f(m_parameters["U_MODEL"], matrix);
	}
}
