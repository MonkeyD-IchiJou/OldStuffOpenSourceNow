#ifndef SSAO_FBO_H
#define SSAO_FBO_H

#include "GLH.h"
#include <vector>
#include "vec3.h"

using namespace Math;
using std::vector;

namespace pp
{

	class ssaobuffer
	{
	public:
		ssaobuffer(void);
		~ssaobuffer(void);

		void Init(const int& rx, const int& ry, const int& kernelSize);

		void BindSSAOBuff(void) const;
		void BindSSAOBlurBuff(void);

		void BindSSAOColorTex(void) const;
		void BindSSAOColorBlur(void) const;
		void BindNoiseTex(void) const;

		void cleanUp(void);
		
		GLuint getFinalSSAOTex(void) const;

		int ResolutionX, ResolutionY;
		vector<vec3f> ssaoKernel;

		void regenerateKernel(const int & kernelSize);

	private:
		void generateNoiseTexAndKernel(const int& kernelSize);

		GLuint ssaoFBO, ssaoBlurFBO; // two framebuffer
		GLuint ssaoColorBuffer, ssaoColorBufferBlur; // two color buffer
		GLuint noiseTexture;
	};
}

#endif
