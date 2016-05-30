#include "skyboxbuffer.h"
#include "utils.h"
#include <iostream>

#include "engine_common.h"

namespace pp
{
	// 480p = ResolutionX(960), ResolutionY(540)
	// 720p = ResolutionX(1280), ResolutionY(720)
	// 900p = ResolutionX(1600), ResolutionY(900)
	// 1080p = ResolutionX(1920), ResolutionY(1080)
	skyboxbuffer::skyboxbuffer(void) : m_fbo(0), ResolutionX(1600), ResolutionY(900), rboDepth(0), m_textures(0)
	{
	}

	skyboxbuffer::~skyboxbuffer(void)
	{
		clear();
	}

	bool skyboxbuffer::Init(const int &rX, const int &rY)
	{
		ResolutionX = rX;
		ResolutionY = rY;

		// prevent memory leak
		clear();

		// fbo creation
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

		// final texture 
		glGenTextures(1, &m_textures);

		// the skybox tex
		glBindTexture(GL_TEXTURE_2D, m_textures);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ResolutionX, ResolutionY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures, 0);

		// - Create and attach depth buffer (renderbuffer)
		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, ResolutionX, ResolutionX);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

		// last checking
		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", Status);
			return false;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		// restore default FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		return true;
	}

	void skyboxbuffer::receiveBuff(void) const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo); // Write to this framebuffer
		// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
		// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
		// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
		glBlitFramebuffer(0, 0, ResolutionX, ResolutionY, 0, 0, ResolutionX, ResolutionY, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		// set up the suitable viewport for this fbo rendering
		glViewport(0, 0, ResolutionX, ResolutionY);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void skyboxbuffer::BindFinalTex(void) const
	{
		glActiveTexture(SKYBOXFBO_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures);
	}

	void skyboxbuffer::clear()
	{
		if (m_fbo != 0)
		{
			glDeleteFramebuffers(1, &m_fbo);
			m_fbo = 0;
		}

		if (rboDepth != 0)
		{
			glDeleteRenderbuffers(1, &rboDepth);
			rboDepth = 0;
		}

		if (m_textures != 0)
		{
			glDeleteTextures(1, &m_textures);
			m_textures = 0;
		}
	}

	GLuint skyboxbuffer::getFinaltexture(void) const
	{
		return m_textures;
	}
}
