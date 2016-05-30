#include "SSAOShader.h"
#include <sstream>
#include "engine_common.h"

namespace pp
{
	SSAOShader::SSAOShader(void) : ShaderProgram("Content//shader//basic.vertexshader", "Content//shader//ssaoShader.fragmentshader")
	{
		getAllUniformLocations();
	}

	SSAOShader::~SSAOShader(void)
	{
	}

	void SSAOShader::getAllUniformLocations(void)
	{
		m_parameters["U_KERNALSIZE"] = getUniformLocation("kernelSize");
		m_parameters["U_RADIUS"] = getUniformLocation("radius");

		m_parameters["U_TEXTUREUNIT_POS"] = getUniformLocation("gPositionDepth");
		m_parameters["U_TEXTUREUNIT_NORMAL"] = getUniformLocation("gNormal");
		m_parameters["U_TEXTUREUNIT_NOISE"] = getUniformLocation("texNoise");

		m_parameters["U_SCREENSIZE"] = getUniformLocation("gScreenSize");

		m_parameters["U_STRENGTH"] = getUniformLocation("strength");

		for (int i = 0; i < 128; ++i)
		{
			std::ostringstream paramName;
			paramName << "U_SAMPLEKERNEL[" << i << "]";

			std::ostringstream kernalName;
			kernalName << "uSampleKernel[" << i << "]";

			m_parameters[paramName.str()] = getUniformLocation(kernalName.str().c_str());
		}

		// view and projection
		UniformBlockBinding("Matrices", 0);
	}

	void SSAOShader::load_TextureUnit(int positiondepth, int normal, int noise)
	{
		loadU_1i(m_parameters["U_TEXTUREUNIT_POS"], positiondepth);
		loadU_1i(m_parameters["U_TEXTUREUNIT_NORMAL"], normal);
		loadU_1i(m_parameters["U_TEXTUREUNIT_NOISE"], noise);

	}

	void SSAOShader::load_ScreenSize(float x, float y)
	{
		loadU_Vec2f(m_parameters["U_SCREENSIZE"], x, y);
	}

	void SSAOShader::load_SampleKernel(vector<vec3f>& samples)
	{
		int i = 0;
		for (vector<vec3f>::iterator it = samples.begin(); it != samples.end(); ++it)
		{
			std::ostringstream paramName;
			paramName << "U_SAMPLEKERNEL[" << i << "]";

			loadU_Vec3f(m_parameters[paramName.str()], samples[i]);

			i++;
		}
	}

	void SSAOShader::load_Radius(const float & radius)
	{
		loadU_1f(m_parameters["U_RADIUS"], radius);
	}

	void SSAOShader::load_Strength(const float & strength)
	{
		loadU_1f(m_parameters["U_STRENGTH"], strength);
	}

	void SSAOShader::load_KernelSize(const int& size)
	{
		loadU_1i(m_parameters["U_KERNALSIZE"], size);
	}
}
