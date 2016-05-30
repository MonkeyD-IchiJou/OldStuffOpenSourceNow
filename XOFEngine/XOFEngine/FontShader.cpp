#include "FontShader.h"


namespace pp
{
	FontShader::FontShader(void) : ShaderProgram("Content//shader//font.vertexshader", "Content//shader//font.fragmentshader")
	{
		getAllUniformLocations();
	}

	FontShader::~FontShader(void)
	{
	}

	void FontShader::load_color(const vec3f& color)
	{
		loadU_Vec3f(m_parameters["U_COLOR"], color);
	}

	void FontShader::load_TextureUnit(const int& i)
	{
		loadU_1i(m_parameters["U_FONTATLAS"], i);
	}

	void FontShader::load_FontMaterial(const FontMaterial &f)
	{
		loadU_1f(m_parameters["U_WIDTH"], f.width);
		loadU_1f(m_parameters["U_EDGE"], f.edge);
		loadU_1f(m_parameters["U_BORDERWIDTH"], f.borderwidth);
		loadU_1f(m_parameters["U_BORDEREDGE"], f.borderedge);
		loadU_Vec2f(m_parameters["U_OFFSET"], f.offsetx, f.offsety);
		loadU_Vec3f(m_parameters["U_OUTLINECOLOR"], f.coloroutline);
	}

	void FontShader::load_Alpha(const float & a)
	{
		loadU_1f(m_parameters["U_ALPHA"], a);
	}

	void FontShader::load_Translation(const mat4f & translate)
	{
		loadU_Mat4f(m_parameters["U_TRANSLATIONMAT"], translate);
	}

	void FontShader::load_Translation(const vec3f & translate)
	{
		loadU_Vec3f(m_parameters["U_TRANSLATION"], translate);
	}

	void FontShader::load_Rotation(const mat4f & m)
	{
		loadU_Mat4f(m_parameters["U_ROTATION"], m);
	}

	void FontShader::load_MiddleTranslate(const mat4f & m)
	{
		loadU_Mat4f(m_parameters["U_MIDDLETRANSLATE"], m);
	}

	void FontShader::load_Mode(const int & m)
	{
		loadU_1i(m_parameters["U_MODE"], m);
	}

	void FontShader::getAllUniformLocations(void)
	{
		m_parameters["U_COLOR"] = getUniformLocation("color");
		m_parameters["U_FONTATLAS"] = getUniformLocation("fontAtlas");
		m_parameters["U_TRANSLATION"] = getUniformLocation("translation");
		m_parameters["U_ROTATION"] = getUniformLocation("rotation");
		m_parameters["U_MIDDLETRANSLATE"] = getUniformLocation("middleTranslation");
		m_parameters["U_MODE"] = getUniformLocation("mode");

		m_parameters["U_WIDTH"] = getUniformLocation("width");
		m_parameters["U_EDGE"] = getUniformLocation("edge");
		m_parameters["U_BORDERWIDTH"] = getUniformLocation("borderwidth");
		m_parameters["U_BORDEREDGE"] = getUniformLocation("borderedge");
		m_parameters["U_OFFSET"] = getUniformLocation("offset");
		m_parameters["U_OUTLINECOLOR"] = getUniformLocation("outlineColor");

		m_parameters["U_TRANSLATIONMAT"] = getUniformLocation("translationmat");

		m_parameters["U_ALPHA"] = getUniformLocation("alphaU");

		// view and projection
		UniformBlockBinding("Matrices", 0);
	}
}