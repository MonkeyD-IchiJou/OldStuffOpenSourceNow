#include "pbuffer.h"
#include "utils.h"
#include "engine_common.h"

#define BRIGHTNESS_ATTACH		GL_COLOR_ATTACHMENT0
#define LOWRES_ATTACH			GL_COLOR_ATTACHMENT1
#define LENSFLARE_ATTACH		GL_COLOR_ATTACHMENT2

#define NULL 0

namespace pp
{
	pbuffer::pbuffer(void) : m_fbo(0), ResolutionX(400), ResolutionY(225)
	{
		for (int i = 0; i < PBUFFER_NUM_TEXTURES; ++i)
		{
			m_textures[i] = 0;
		}
	}

	pbuffer::~pbuffer(void)
	{
		if (m_fbo != 0)
		{
			glDeleteFramebuffers(1, &m_fbo);
			m_fbo = 0;
		}

		if (m_textures[0] != 0)
		{
			glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures);

			for (int i = 0; i < PBUFFER_NUM_TEXTURES; ++i)
			{
				m_textures[i] = 0;
			}
		}
	}

	bool pbuffer::Init(int rX, int rY)
	{
		this->ResolutionX = rX;
		this->ResolutionY = rY;

		// Framebuffers
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		// create textures for these framebuffer
		m_textures[PBUFFER_TEXTURE_TYPE_BRIGHTNESS] = generateAttachmentTexture();
		glFramebufferTexture2D(GL_FRAMEBUFFER, BRIGHTNESS_ATTACH, GL_TEXTURE_2D, m_textures[PBUFFER_TEXTURE_TYPE_BRIGHTNESS], 0);	// the brightness only

		m_textures[PBUFFER_TEXTURE_TYPE_LOWRES] = generateAttachmentTexture();
		glFramebufferTexture2D(GL_FRAMEBUFFER, LOWRES_ATTACH, GL_TEXTURE_2D, m_textures[PBUFFER_TEXTURE_TYPE_LOWRES], 0);	// low res de

		m_textures[PBUFFER_TEXTURE_TYPE_LENSFLARE] = generateAttachmentTexture();
		glFramebufferTexture2D(GL_FRAMEBUFFER, LENSFLARE_ATTACH, GL_TEXTURE_2D, m_textures[PBUFFER_TEXTURE_TYPE_LENSFLARE], 0);	// the lens flare

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw 0;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	void pbuffer::startFrame(void) const
	{
		glViewport(0, 0, ResolutionX, ResolutionY);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo); // write to this framebuffer
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void pbuffer::prepareAttachments(void) const
	{
		// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
		GLuint attachments[2] = { BRIGHTNESS_ATTACH, LOWRES_ATTACH };
		glDrawBuffers(2, attachments);
	}

	void pbuffer::drawForLensflare(void) const
	{
		// draw to the texture buffer attachment 2
		glDrawBuffer(LENSFLARE_ATTACH);
	}

	void pbuffer::BindBrightnessTex(void) const
	{
		glActiveTexture(BRIGHTNESS_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[PBUFFER_TEXTURE_TYPE_BRIGHTNESS]);
	}

	void pbuffer::BindLowResTex(void) const
	{
		glActiveTexture(LOWRES_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[PBUFFER_TEXTURE_TYPE_LOWRES]);
	}

	void pbuffer::BindLensFlareTex(void) const
	{
		glActiveTexture(LENSFLARE_TEXTURE_UNIT);
		glBindTexture(GL_TEXTURE_2D, m_textures[PBUFFER_TEXTURE_TYPE_LENSFLARE]);
	}

	GLuint pbuffer::generateAttachmentTexture(void)
	{
		//Generate texture ID and load texture data 
		GLuint textureID =0;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, _RGB, ResolutionX, ResolutionY, 0, GL_RGB, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);       // try change to GL_CLAMP or GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glBindTexture(GL_TEXTURE_2D, 0);

		return textureID;
	}
}