#include "GeometryPassShader.h"
#include <sstream>

namespace pp
{
	GeometryPassShader::GeometryPassShader(void) : ShaderProgram("Content//shader//geometrypass.vertexshader", "Content//shader//geometrypass.fragmentshader")
	{
		getAllUniformLocations();
	}


	GeometryPassShader::~GeometryPassShader(void)
	{
	}
	
	void GeometryPassShader::load_ModelMatrix(const mat4f & matrix)
	{
		loadU_Mat4f(m_parameters["U_MODEL"], matrix);
	}

	void GeometryPassShader::load_PrevModelViewProjectionMatrix(const mat4f & matrix)
	{
		loadU_Mat4f(m_parameters["U_PREVMVP"], matrix);
	}

	void GeometryPassShader::load_LightMatrix(const mat4f & mat)
	{
		loadU_Mat4f(m_parameters["U_LIGHTMAT"], mat);
	}

	void GeometryPassShader::load_DepthTex(const int & i)
	{
		loadU_1i(m_parameters["U_SHADOWTEX"], i);
	}

	void GeometryPassShader::load_Color(const vec3f& color)
	{
		loadU_Vec3f(m_parameters["U_COLOR"], color);
	}

	void GeometryPassShader::load_Shininess(const float& s)
	{
		loadU_1f(m_parameters["U_SHININESS"], s);
	}

	void GeometryPassShader::load_Emissive(const float & e)
	{
		loadU_1f(m_parameters["U_EMISSIVE"], e);
	}

	void GeometryPassShader::load_LightDir(const vec3f & lightdir)
	{
		loadU_Vec3f(m_parameters["U_LIGHTDIR"], lightdir);
	}

	void GeometryPassShader::getAllUniformLocations(void)
	{
		// basic
		m_parameters["U_MODEL"] = getUniformLocation("Model");
		m_parameters["U_PREVMVP"] = getUniformLocation("uPrevModelViewProjectionMat");

		// material stuff
		m_parameters["U_SHININESS"] = getUniformLocation("shininess");
		m_parameters["U_COLOR"] = getUniformLocation("objcolor");
		m_parameters["U_EMISSIVE"] = getUniformLocation("emissive");

		m_parameters["U_SHADOWTEX"] = getUniformLocation("shadowMap");
		m_parameters["U_LIGHTMAT"] = getUniformLocation("lightSpaceMatrix");

		m_parameters["U_LIGHTDIR"] = getUniformLocation("lightDir");

		// view and projection
		UniformBlockBinding("Matrices", 0);

		
	}

	

}
