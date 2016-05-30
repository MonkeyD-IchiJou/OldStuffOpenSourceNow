#include "depthMapFBO.h"
#include "engine_common.h"

namespace pp
{
	depthMapFBO::depthMapFBO(void) : depthFBO(0), depthMap(0)
	{
	}

	depthMapFBO::~depthMapFBO()
	{
		clear();
	}

	void depthMapFBO::Init(int SCR_WIDTH, int SCR_HEIGHT)
	{
		clear();

		ResolutionX = SCR_WIDTH;
		ResolutionY = SCR_HEIGHT;

		glGenFramebuffers(1, &depthFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);

		// - Create depth texture
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ResolutionX, ResolutionY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		// Also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw 0;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void depthMapFBO::prepareForDrawing(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void depthMapFBO::bindDepthMap(const GLenum& active) const
	{
		glActiveTexture(active);
		glBindTexture(GL_TEXTURE_2D, depthMap);
	}

	void depthMapFBO::clear(void)
	{
		if (depthFBO!=0)
		{
			glDeleteFramebuffers(1, &depthFBO);
			depthFBO = 0;
		}

		if (depthMap != 0)
		{
			glDeleteTextures(1, &depthMap);
			depthMap = 0;
		}
	}
}
