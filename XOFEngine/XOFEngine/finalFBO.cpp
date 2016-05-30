#include "finalFBO.h"
#include "engine_common.h"

#define MOTION_BLUR_ATTACH		GL_COLOR_ATTACHMENT0
#define FINAL_PP_ATTACH			GL_COLOR_ATTACHMENT1

namespace pp
{
	finalFBO::finalFBO(void) : ppFBO(0), m_motionblurtex(0), ResolutionX(0), ResolutionY(0), m_finalTex(0)
	{
	}


	finalFBO::~finalFBO(void)
	{
		if (ppFBO != 0)
		{
			glDeleteFramebuffers(1, &ppFBO);
			ppFBO = 0;
		}

		if (m_motionblurtex != 0)
		{
			glDeleteTextures(1, &m_motionblurtex);
			m_motionblurtex = 0;
		}

		if (m_finalTex != 0)
		{
			glDeleteTextures(1, &m_finalTex);
			m_finalTex = 0;
		}
	}

	void finalFBO::prepareMotionBlurPass(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ppFBO);
		glDrawBuffer(MOTION_BLUR_ATTACH);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void finalFBO::prepareFinalPass(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ppFBO);
		glDrawBuffer(FINAL_PP_ATTACH);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void finalFBO::bindMotionBlurTex(void) const
	{
		glActiveTexture(MOTIONBLURFBO_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_motionblurtex);
	}

	void finalFBO::bindFinalTex(void) const
	{
		glActiveTexture(FINALFINAL_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_finalTex);
	}

	void finalFBO::Init(int SCR_WIDTH, int SCR_HEIGHT)
	{
		ResolutionX = SCR_WIDTH;
		ResolutionY = SCR_HEIGHT;
		
		glGenFramebuffers(1, &ppFBO);
		glGenTextures(1, &m_motionblurtex);
		glGenTextures(1, &m_finalTex);

		glBindFramebuffer(GL_FRAMEBUFFER, ppFBO);

		glBindTexture(GL_TEXTURE_2D, m_motionblurtex);
		glTexImage2D(GL_TEXTURE_2D, 0, _RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // We clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_FRAMEBUFFER, MOTION_BLUR_ATTACH, GL_TEXTURE_2D, m_motionblurtex, 0);

		glBindTexture(GL_TEXTURE_2D, m_finalTex);
		glTexImage2D(GL_TEXTURE_2D, 0, _RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // We clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_FRAMEBUFFER, FINAL_PP_ATTACH, GL_TEXTURE_2D, m_finalTex, 0);


		// Also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw 0;
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
