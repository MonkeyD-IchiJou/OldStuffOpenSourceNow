#include "debugShader.h"


namespace pp
{
	debugShader::debugShader(void) : ShaderProgram("Content//shader//debug.vertexshader", "Content//shader//debug.fragmentshader")
	{
		getAllUniformLocations();
	}

	debugShader::~debugShader(void)
	{
	}

	void debugShader::load_color(const vec3f & color)
	{
		loadU_Vec3f(m_parameters["COLOR"], color);
	}

	void debugShader::getAllUniformLocations(void)
	{
		m_parameters["COLOR"] = getUniformLocation("color");
		// view and projection
		UniformBlockBinding("Matrices", 0);
	}
}