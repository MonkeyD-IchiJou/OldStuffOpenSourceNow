#ifndef SSAO_SHADER_H
#define SSAO_SHADER_H

#include "ShaderProgram.h"
#include <map>
#include <vector>
#include <string>
using std::map;
using std::vector;
using std::string;

namespace pp
{
	class SSAOShader :
		public ShaderProgram
	{
	public:
		SSAOShader(void);
		~SSAOShader(void);

		void load_TextureUnit(int positiondepth, int normal, int noise);
		void load_ScreenSize(float x, float y);

		void load_SampleKernel(vector<vec3f>&samples);

		void load_KernelSize(const int& size);

		void load_Radius(const float& radius);
		void load_Strength(const float& strength);
		
	private:
		map<string, unsigned int> m_parameters;

	protected:

		// get all the uniform location info into m_parameters[]
		void getAllUniformLocations(void);
	};
}

#endif

