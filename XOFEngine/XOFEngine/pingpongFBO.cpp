#include "pingpongFBO.h"
#include <iostream>
#include "utils.h"
#include "engine_common.h"

namespace pp
{
	pingpongFBO::pingpongFBO(void) : ResolutionX(0), ResolutionY(0)
	{
		ZERO_MEM(ppFBO);
		ZERO_MEM(ppColorbuffers);
	}

	pingpongFBO::~pingpongFBO(void)
	{
		clear();
	}

	void pingpongFBO::Init(const int & rX, const int & rY)
	{
		// prevent memory leak
		clear();

		ResolutionX = rX;
		ResolutionY = rY;

		glGenFramebuffers(2, ppFBO);
		glGenTextures(2, ppColorbuffers);

		for (GLuint i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ppFBO[i]);
			glBindTexture(GL_TEXTURE_2D, ppColorbuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, _RGB, rX, rY, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ppColorbuffers[i], 0);
			// Also check if framebuffers are complete (no need for depth buffer)
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Framebuffer not complete!" << std::endl;
		}
	}

	void pingpongFBO::clear(void)
	{
		if (ppFBO[0] == 0)
		{
			glDeleteFramebuffers(2, ppFBO);
			ZERO_MEM(ppFBO);
		}

		if (ppColorbuffers[0] == 0)
		{
			glDeleteTextures(2, ppColorbuffers);
			ZERO_MEM(ppColorbuffers);
		}
	}
	void pingpongFBO::viewPortUpdate(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
	}
	void pingpongFBO::bindFBO(const GLuint & i) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ppFBO[i]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void pingpongFBO::bindTex(const GLenum & active, const GLuint & i) const
	{
		glActiveTexture(active);
		glBindTexture(GL_TEXTURE_2D, ppColorbuffers[i]);
	}
}