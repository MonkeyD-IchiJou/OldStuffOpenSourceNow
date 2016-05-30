#include "ssaobuffer.h"
#include <iostream>
#include <random> // necessary for generation of random floats (for sample kernel and noise texture)
#include "engine_common.h"

namespace pp
{
	// 480p = ResolutionX(960), ResolutionY(540)
	// 720p = ResolutionX(1280), ResolutionY(720)
	// 900p = ResolutionX(1600), ResolutionY(900)
	// 1080p = ResolutionX(1920), ResolutionY(1080)
	ssaobuffer::ssaobuffer(void) : ResolutionX(960), ResolutionY(540), ssaoFBO(0), ssaoBlurFBO(0), ssaoColorBuffer(0), ssaoColorBufferBlur(0), noiseTexture(0)
	{
	}

	ssaobuffer::~ssaobuffer(void)
	{
		cleanUp();
	}

	void ssaobuffer::Init(const int& rx, const int& ry, const int& kernelSize)
	{
		this->ResolutionX = rx;
		this->ResolutionY = ry;

		glGenFramebuffers(1, &ssaoFBO);
		glGenFramebuffers(1, &ssaoBlurFBO);

		// - SSAO color buffer
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
		glGenTextures(1, &ssaoColorBuffer);
		glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, ResolutionX, ResolutionY, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "SSAO Framebuffer not complete!" << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		// - and blur stage
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
		glGenTextures(1, &ssaoColorBufferBlur);
		glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, ResolutionX, ResolutionY, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);


		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		generateNoiseTexAndKernel(kernelSize);
	}
	
	GLfloat lerp(GLfloat a, GLfloat b, GLfloat f)
	{
		return a + f * (b - a);
	}

	void ssaobuffer::regenerateKernel(const int & kernelSize)
	{
		std::default_random_engine generator;
		std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0


		// sample kernel
		for (GLuint i = 0; i < (unsigned int) kernelSize; ++i)
		{
			vec3f sample(randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator));
			sample.normalize();// = glm::normalize(sample);

			sample *= randomFloats(generator);

			GLfloat scale = GLfloat(i) / kernelSize;

			// Scale samples s.t. they're more aligned to center of kernel
			scale = lerp(0.1f, 1.0f, scale * scale);
			sample *= scale;
			ssaoKernel.push_back(sample);
		}
	}

	void ssaobuffer::generateNoiseTexAndKernel(const int& kernelSize)
	{
		std::default_random_engine generator;
		std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0


		// sample kernel
		for (GLuint i = 0; i < (unsigned int)kernelSize; ++i)
		{
			vec3f sample(randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator));
			sample.normalize();// = glm::normalize(sample);

			sample *= randomFloats(generator);

			GLfloat scale = GLfloat(i) / kernelSize;

			// Scale samples s.t. they're more aligned to center of kernel
			scale = lerp(0.1f, 1.0f, scale * scale);
			sample *= scale;
			ssaoKernel.push_back(sample);
		}


		// Noise texture
		std::vector<vec3f> ssaoNoise;
		for (GLuint i = 0; i < (16); i++)
		{
			vec3f noise(randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator) * 2.0f - 1.0f, 0.0f); // rotate around z-axis (in tangent space)
			ssaoNoise.push_back(noise);
		}
		glGenTextures(1, &noiseTexture);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, &ssaoNoise[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void ssaobuffer::BindSSAOBuff(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ssaobuffer::BindSSAOBlurBuff(void)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ssaobuffer::BindSSAOColorTex(void) const
	{
		glActiveTexture(SSAO_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
	}

	void ssaobuffer::BindSSAOColorBlur(void) const
	{
		glActiveTexture(SSAOBLUR_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
	}

	void ssaobuffer::BindNoiseTex(void) const
	{
		glActiveTexture(NOISE_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);
	}


	GLuint ssaobuffer::getFinalSSAOTex(void) const
	{
		return ssaoColorBufferBlur;
	}


	void ssaobuffer::cleanUp(void)
	{
		if (ssaoFBO != 0)
		{
			glDeleteFramebuffers(1, &ssaoFBO);
			ssaoFBO = 0;
		}

		if (ssaoBlurFBO != 0)
		{
			glDeleteFramebuffers(1, &ssaoBlurFBO);
			ssaoBlurFBO = 0;
		}

		if (ssaoColorBuffer != 0)
		{
			glDeleteTextures(1, &ssaoColorBuffer);
			ssaoColorBuffer = 0;
		}

		if (ssaoColorBufferBlur != 0)
		{
			glDeleteTextures(1, &ssaoColorBufferBlur);
			ssaoColorBufferBlur = 0;
		}

		if (noiseTexture != 0)
		{
			glDeleteTextures(1, &noiseTexture);
			noiseTexture = 0;
		}

		ssaoKernel.clear();
	}
}
