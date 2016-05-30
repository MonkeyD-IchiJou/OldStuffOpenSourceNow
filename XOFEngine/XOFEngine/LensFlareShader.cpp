#include "LensFlareShader.h"

namespace pp
{
	LensFlareShader::LensFlareShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//LensFlareShader.fragmentshader")
	{
		getAllUniformLocations();
	}


	LensFlareShader::~LensFlareShader(void)
	{

	}

	void LensFlareShader::load_TexUnit(int brightness, int lenscolor)
	{
		loadU_1i(m_parameters["U_TEXUNIT"], brightness);
		loadU_1i(m_parameters["U_LENSCOLOR"], lenscolor);
	}

	void LensFlareShader::load_NumOfGhost(int i)
	{
		loadU_1i(m_parameters["U_NUMGHOST"], i);
	}

	void LensFlareShader::load_GhostDispersal(float g)
	{
		loadU_1f(m_parameters["U_GHOSTDISPERSAL"], g);
	}

	void LensFlareShader::load_HaloWidth(float w)
	{
		loadU_1f(m_parameters["U_HALOWIDTH"], w);
	}

	void LensFlareShader::load_Distortion(float distortion)
	{
		loadU_1f(m_parameters["U_DISTORTION"], distortion);
	}

	void LensFlareShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEXUNIT"] = getUniformLocation("uInputTex");
		m_parameters["U_LENSCOLOR"] = getUniformLocation("uLensColor");
		m_parameters["U_NUMGHOST"] = getUniformLocation("uGhosts");
		m_parameters["U_GHOSTDISPERSAL"] = getUniformLocation("uGhostDispersal");
		m_parameters["U_HALOWIDTH"] = getUniformLocation("uHaloWidth");
		m_parameters["U_DISTORTION"] = getUniformLocation("uDistortion");
	}
}
