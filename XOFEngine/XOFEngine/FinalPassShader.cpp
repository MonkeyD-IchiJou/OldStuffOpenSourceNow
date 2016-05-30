#include "FinalPassShader.h"


namespace pp
{
	FinalPassShader::FinalPassShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//finalPassShader.fragmentshader")
	{
		getAllUniformLocations();
	}

	FinalPassShader::~FinalPassShader(void)
	{
	}

	void FinalPassShader::getAllUniformLocations(void)
	{
		m_parameters["U_TEXTUREUNIT"] = getUniformLocation("texUnit");

		m_parameters["U_BLOOMUNIT"] = getUniformLocation("bloomBlur");
		m_parameters["U_BLOOM"] = getUniformLocation("bloom");

		m_parameters["U_LENSFLAREUNIT"] = getUniformLocation("lensflareTex");
		m_parameters["U_LENS"] = getUniformLocation("lensflare");

		m_parameters["U_LENSDIRT"] = getUniformLocation("uLensDirtTex");
		m_parameters["U_LENSSTAR"] = getUniformLocation("uLensStarTex");

		m_parameters["U_LENSSTARMAT4"] = getUniformLocation("uLensStarMatrix");

		m_parameters["U_FADE"] = getUniformLocation("fade");
	}

	void FinalPassShader::load_TextureUnit(const int& i)
	{
		loadU_1i(m_parameters["U_TEXTUREUNIT"], i);
	}
	void FinalPassShader::load_BloomTextureUnit(const int& i)
	{
		loadU_1i(m_parameters["U_BLOOMUNIT"], i);
	}
	void FinalPassShader::load_LensFlareTextureUnit(const int& i)
	{
		loadU_1i(m_parameters["U_LENSFLAREUNIT"], i);
	}
	void FinalPassShader::load_LensFlareEnable(const bool& e)
	{
		loadU_Bool(m_parameters["U_LENS"], e);
	}
	void FinalPassShader::load_LensPostProcess(const int& dirt, const int& star)
	{
		loadU_1i(m_parameters["U_LENSDIRT"], dirt);
		loadU_1i(m_parameters["U_LENSSTAR"], star);
	}
	void FinalPassShader::load_BloomEnable(const bool& e)
	{
		loadU_Bool(m_parameters["U_BLOOM"], e);
	}
	void FinalPassShader::load_LensStartMatrix(mat4f & matrix)
	{
		loadU_Mat4f(m_parameters["U_LENSSTARMAT4"], matrix);
	}

	void FinalPassShader::load_FadeValue(const float & fade)
	{
		loadU_1f(m_parameters["U_FADE"], fade);
	}

}
