#include "commonShader.h"


namespace pp
{
	commonShader::commonShader(void) : ShaderProgram("Content//shader//common.vertexshader", "Content//shader//debug.fragmentshader")
	{
		getAllUniformLocations();
	}

	commonShader::~commonShader(void)
	{
	}

	void commonShader::getAllUniformLocations(void)
	{
		m_parameters["U_MODEL"] = getUniformLocation("model");
		m_parameters["COLOR"] = getUniformLocation("color");
		// view and projection
		UniformBlockBinding("Matrices", 0);
	}

	void commonShader::load_color(const vec3f & color)
	{
		loadU_Vec3f(m_parameters["COLOR"], color);
	}

	void commonShader::load_ModelMatrix(const mat4f& m)
	{
		loadU_Mat4f(m_parameters["U_MODEL"], m);


	}
}