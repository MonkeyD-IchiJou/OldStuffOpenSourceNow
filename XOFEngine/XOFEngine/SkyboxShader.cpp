#include "SkyboxShader.h"

namespace pp
{

	SkyboxShader::SkyboxShader(void) : ShaderProgram("Content//shader//skyboxShader.vertexshader", "Content//shader//skyboxShader.fragmentshader")
	{
		getAllUniformLocations();
	}

	SkyboxShader::~SkyboxShader(void)
	{
	}
	void SkyboxShader::getAllUniformLocations(void)
	{

		// view and projection
		UniformBlockBinding("Matrices", 0);
	}

	
	
}

