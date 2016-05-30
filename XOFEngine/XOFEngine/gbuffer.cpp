#include "gbuffer.h"
#include "utils.h"
#include <iostream>
#include "engine_common.h"

#define POS_ATTACHMENT				GL_COLOR_ATTACHMENT0
#define NORM_ATTACHMENT				GL_COLOR_ATTACHMENT1
#define DIFF_ATTACHMENT				GL_COLOR_ATTACHMENT2
#define NORMVIEW_ATTACHMENT			GL_COLOR_ATTACHMENT3
#define POSVIEW_ATTACHMENT			GL_COLOR_ATTACHMENT4
#define VEL_ATTACHMENT				GL_COLOR_ATTACHMENT5
#define FINAL_ATTACHMENT			GL_COLOR_ATTACHMENT6


namespace pp
{
	// 480p = ResolutionX(960), ResolutionY(540)
	// 720p = ResolutionX(1280), ResolutionY(720)
	// 900p = ResolutionX(1600), ResolutionY(900)
	// 1080p = ResolutionX(1920), ResolutionY(1080)
	gbuffer::gbuffer(void) : m_fbo(0), m_finalTexture(0), ResolutionX(1280), ResolutionY(720), rboDepth(0)
	{
		for (int i = 0; i < GBUFFER_NUM_TEXTURES; ++i)
		{
			m_textures[i] = 0;
		}
	}

	gbuffer::~gbuffer(void)
	{
		clear();
	}

	bool gbuffer::Init(const int & rx, const int& ry)
	{
		// prevent memory leak
		clear();

		ResolutionX = rx;
		ResolutionY = ry;

		// fbo creation
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

		unsigned int sizeofgbuffer = ARRAY_SIZE_IN_ELEMENTS(m_textures);
		// create gbuffer textures
		glGenTextures(sizeofgbuffer, m_textures);
		// final texture 
		glGenTextures(1, &m_finalTexture);

		// position is special, last component if for depth
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION]);
		glTexImage2D(GL_TEXTURE_2D, 0, RGBA, ResolutionX, ResolutionY, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, POS_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION], 0);

		// normal
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL]);
		glTexImage2D(GL_TEXTURE_2D, 0, RGBA, ResolutionX, ResolutionY, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, NORM_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL], 0);

		// diffuse
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_DIFFUSE]);
		glTexImage2D(GL_TEXTURE_2D, 0, RGBA, ResolutionX, ResolutionY, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, DIFF_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_DIFFUSE], 0);

		// normal in view space
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL_VIEW]);
		glTexImage2D(GL_TEXTURE_2D, 0, _RGB, ResolutionX, ResolutionY, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, NORMVIEW_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL_VIEW], 0);

		// position in view space
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION_VIEW]);
		glTexImage2D(GL_TEXTURE_2D, 0, RGBA, ResolutionX, ResolutionY, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, POSVIEW_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION_VIEW], 0);

		// velocity
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_VELOCITY]);
		glTexImage2D(GL_TEXTURE_2D, 0, RG, ResolutionX, ResolutionY, 0, GL_RG, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, VEL_ATTACHMENT, GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_VELOCITY], 0);

		// - Create and attach depth buffer (renderbuffer)
		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ResolutionX, ResolutionX);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

		// final // final output // consider HDR method
		glBindTexture(GL_TEXTURE_2D, m_finalTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, _RGB, ResolutionX, ResolutionY, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, FINAL_ATTACHMENT, GL_TEXTURE_2D, m_finalTexture, 0);

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

	void gbuffer::startFrame(void) const
	{
		// set up the suitable viewport for this fbo rendering
		glViewport(0, 0, ResolutionX, ResolutionY);

		// bind the fbo and begin gpass
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

		// draw to last texture
		glDrawBuffer(FINAL_ATTACHMENT);

		glClear(GL_COLOR_BUFFER_BIT);
		
	}

	void gbuffer::PrepareForGeoPassDrawing(void) const
	{
		GLenum DrawBuffers[] =
		{
			POS_ATTACHMENT, // position
			NORM_ATTACHMENT, // normal
			DIFF_ATTACHMENT, // diffuse
			NORMVIEW_ATTACHMENT,
			POSVIEW_ATTACHMENT,
			VEL_ATTACHMENT
		};	

		glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);
	}

	void gbuffer::PrepareForLightPass(void) const
	{
		// note : the fbo need to bind before this function 

		// output to the final texture
		glDrawBuffer(FINAL_ATTACHMENT);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void gbuffer::PreBindForLightPass(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	}

	void gbuffer::readBuff(void) const
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	}

	void gbuffer::BindPositionTex(void) const
	{
		glActiveTexture(POSITION_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION]);
	}

	void gbuffer::BindNormalTex(void) const
	{
		glActiveTexture(NORMAL_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL]);
	}

	void gbuffer::BindDiffuseTex(void) const
	{
		glActiveTexture(DIFF_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_DIFFUSE]);
	}

	void gbuffer::BindPositionViewTex(void) const
	{
		glActiveTexture(POSITION_VIEW_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_POSITION_VIEW]);
	}

	void gbuffer::BindNormalViewTex(void) const
	{
		glActiveTexture(NORMAL_VIEW_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_NORMAL_VIEW]);
	}

	void gbuffer::BindVelTex(void) const
	{
		glActiveTexture(VEL_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[GBUFFER_TEXTURE_TYPE_VELOCITY]);
	}

	void gbuffer::BindFinalTex(void) const
	{
		glActiveTexture(FINAL_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_finalTexture);
	}

	void gbuffer::clear()
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

		if (m_textures[0] != 0)
		{
			glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures);

			for (int i = 0; i < GBUFFER_NUM_TEXTURES; ++i)
			{
				m_textures[i] = 0;
			}
		}

		if (m_finalTexture != 0)
		{
			glDeleteTextures(1, &m_finalTexture);

			m_finalTexture = 0;
		}
	}

	GLuint gbuffer::getPostexture(void) const
	{
		return m_textures[GBUFFER_TEXTURE_TYPE_POSITION];
	}

	GLuint gbuffer::getNormtexture(void) const
	{
		return m_textures[GBUFFER_TEXTURE_TYPE_NORMAL];
	}

	GLuint gbuffer::getDifftexture(void) const
	{
		return m_textures[GBUFFER_TEXTURE_TYPE_DIFFUSE];
	}

	GLuint gbuffer::getNormViewtexture(void) const
	{
		return m_textures[GBUFFER_TEXTURE_TYPE_NORMAL_VIEW];
	}

	GLuint gbuffer::getPosViewtexture(void) const
	{
		return m_textures[GBUFFER_TEXTURE_TYPE_POSITION_VIEW];
	}

	GLuint gbuffer::getVeltexture(void) const
	{
		return m_textures[GBUFFER_TEXTURE_TYPE_VELOCITY];
	}

	GLuint gbuffer::getFinaltexture(void) const
	{
		return m_finalTexture;
	}
}
