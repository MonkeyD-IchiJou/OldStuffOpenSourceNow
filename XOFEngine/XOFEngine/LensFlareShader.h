#ifndef LENS_FLARE_SHADER_H
#define LENS_FLARE_SHADER_H

#include "ShaderProgram.h"

#include <map>
#include <string>
using std::map;
using std::string;

namespace pp
{
	class LensFlareShader :
		public ShaderProgram
	{
	public:
		LensFlareShader(void);
		virtual ~LensFlareShader(void);

		void load_TexUnit(int brightness, int lenscolor);
		void load_NumOfGhost(int i);
		void load_GhostDispersal(float g);
		void load_HaloWidth(float w);
		void load_Distortion(float distortion);

	private:
		map<string, unsigned int> m_parameters;

	protected:
		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif
