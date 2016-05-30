#include "GrassShader.h"

namespace pp
{

	GrassShader::GrassShader(void) : ShaderProgram("Content//shader//grassShader.vertexshader", "Content//shader//grassShader.fragmentshader", "Content//shader//grassShader.geometryshader")
	{
		getAllUniformLocations();
	}

	GrassShader::~GrassShader(void)
	{
	}

	void GrassShader::load_ModelMatrix(const mat4f & m)
	{
		loadU_Mat4f(m_parameters["U_MODEL"], m);
	}

	void GrassShader::load_Timer(const float & timer)
	{
		loadU_1f(m_parameters["U_TIMER"], timer);
	}

	void GrassShader::load_WindDir(const vec3f & wd)
	{
		loadU_Vec3f(m_parameters["U_WINDIR"], wd);
	}

	void GrassShader::getAllUniformLocations(void)
	{
		m_parameters["U_MODEL"] = getUniformLocation("Model");
		m_parameters["U_TIMER"] = getUniformLocation("m_Timer");
		m_parameters["U_WINDIR"] = getUniformLocation("windDirection");
		
		// view and projection
		UniformBlockBinding("Matrices", 0);
	}

	
	
}

