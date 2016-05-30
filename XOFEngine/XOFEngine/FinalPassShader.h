#ifndef FINALPASS_SHADER_H
#define FINALPASS_SHADER_H

#include "ShaderProgram.h"
#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class FinalPassShader :
		public ShaderProgram
	{
	public:
		FinalPassShader(void);
		~FinalPassShader(void);

		void load_TextureUnit(const int& i);
		void load_BloomTextureUnit(const int& i);
		void load_LensFlareTextureUnit(const int& i);
		void load_LensFlareEnable(const bool& e);
		void load_LensPostProcess(const int& dirt, const int& star);
		void load_BloomEnable(const bool& e);
		void load_LensStartMatrix(mat4f &matrix);

		void load_FadeValue(const float& fade);

	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

