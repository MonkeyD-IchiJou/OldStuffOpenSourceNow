#include "LightShader.h"
#include "DirLightC.h"
#include "PointLightC.h"

namespace pp
{
	LightShader::LightShader(void) : ShaderProgram("Content//shader//lightpass.vertexshader", "Content//shader//lightpass.fragmentshader")
	{
		getAllUniformLocations();
	}


	LightShader::~LightShader(void)
	{
	}


	void LightShader::getAllUniformLocations(void)
	{
		m_parameters["U_POSITIONTEX_UNIT"] = getUniformLocation("gPosition");
		m_parameters["U_NORMALTEX_UNIT"] = getUniformLocation("gNormal");
		m_parameters["U_DIFFUSETEX_UNIT"] = getUniformLocation("gDiffuse");
		m_parameters["U_SSAOTEX_UNIT"] = getUniformLocation("ssao");


		m_parameters["U_LIGHTDIRECTION"] = getUniformLocation("dirlight.direction");
		m_parameters["U_LIGHTCOLOR"] = getUniformLocation("dirlight.color");
		m_parameters["U_LIGHTAMBIENT"] = getUniformLocation("dirlight.ambient");
		m_parameters["U_LIGHTDIFFUSE"] = getUniformLocation("dirlight.diffuse");
		m_parameters["U_LIGHTSPECULAR"] = getUniformLocation("dirlight.specular");

		m_parameters["U_VIEWPOS"] = getUniformLocation("viewPos");
		m_parameters["U_SSAOENABLE"] = getUniformLocation("ssaoEnable");

		m_parameters["U_LIGHTTYPE"] = getUniformLocation("lighttype");

		m_parameters["U_MODELMAT"] = getUniformLocation("Model");
		
		m_parameters["U_PNTLIGHTPOS"] = getUniformLocation("pointlight.position");
		m_parameters["U_PNTLIGHTCOLOR"] = getUniformLocation("pointlight.color");
		m_parameters["U_PNTLIGHTDIFFUSE"] = getUniformLocation("pointlight.diffuse");
		m_parameters["U_PNTLIGHTSPECULAR"] = getUniformLocation("pointlight.specular");

		m_parameters["U_SCREENSIZE"] = getUniformLocation("screensize");

		m_parameters["U_SKYBOX"] = getUniformLocation("skybox");

		// view and projection
		UniformBlockBinding("Matrices", 0);
	}

	

	void LightShader::load_ALLGPASS(const int&  position, const int& normal, const int& diffuse, const int& ssao)
	{
		loadU_1i(m_parameters["U_POSITIONTEX_UNIT"], position);
		loadU_1i(m_parameters["U_NORMALTEX_UNIT"], normal);
		loadU_1i(m_parameters["U_DIFFUSETEX_UNIT"], diffuse);
		loadU_1i(m_parameters["U_SSAOTEX_UNIT"], ssao);
	}


	void LightShader::load_DirLight(const DirLightC& light)
	{
		loadU_Vec3f(m_parameters["U_LIGHTDIRECTION"], light.lightdirection);
		loadU_Vec3f(m_parameters["U_LIGHTCOLOR"], light.lightColor);
		loadU_Vec3f(m_parameters["U_LIGHTAMBIENT"], light.ambient);
		loadU_Vec3f(m_parameters["U_LIGHTDIFFUSE"], light.diffuse);
		loadU_Vec3f(m_parameters["U_LIGHTSPECULAR"], light.specular);
	}

	void LightShader::load_PointLight(const PointLightC & light)
	{
		loadU_Vec3f(m_parameters["U_PNTLIGHTPOS"], light.lightPos);
		loadU_Vec3f(m_parameters["U_PNTLIGHTCOLOR"], light.lightColor);
		loadU_Vec3f(m_parameters["U_PNTLIGHTDIFFUSE"], light.diffuse);
		loadU_Vec3f(m_parameters["U_PNTLIGHTSPECULAR"], light.specular);
	}

	void LightShader::load_ViewPos(const vec3f & v)
	{
		loadU_Vec3f(m_parameters["U_VIEWPOS"], v);
	}

	void LightShader::load_SSAOEnable(const int & i)
	{
		loadU_1i(m_parameters["U_SSAOENABLE"], i);
	}

	void LightShader::load_LightType(const int & type)
	{
		loadU_1i(m_parameters["U_LIGHTTYPE"], type);
	}

	void LightShader::load_ModelMatrix(const mat4f & m)
	{
		loadU_Mat4f(m_parameters["U_MODELMAT"], m);
	}

	void LightShader::load_ScreenSize(const float & x, const float & y)
	{
		loadU_Vec2f(m_parameters["U_SCREENSIZE"], x, y);
	}

	void LightShader::load_SkyboxUnit(const int & i)
	{
		loadU_1i(m_parameters["U_SKYBOX"], i);
	}


	
}