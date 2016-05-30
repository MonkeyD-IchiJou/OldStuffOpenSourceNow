#ifndef FONT_SHADER_H
#define FONT_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;

#include "GUIText.h"

namespace pp
{
	class FontShader :
		public ShaderProgram
	{
	public:
		FontShader(void);
		~FontShader(void);

		void load_Translation(const mat4f & translate);
		void load_Translation(const vec3f & translate);
		void load_Rotation(const mat4f &m);
		void load_MiddleTranslate(const mat4f &m);
		void load_Mode(const int &m);

		void load_color(const vec3f& color);
		void load_TextureUnit(const int& i);
		void load_FontMaterial(const FontMaterial &f);
		void load_Alpha(const float & a);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

