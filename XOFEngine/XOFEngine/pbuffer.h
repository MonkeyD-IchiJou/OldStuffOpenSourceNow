#ifndef PBUFF_H
#define PBUFF_H

#include "GLH.h"

namespace pp
{
	class pbuffer
	{
	public:
		enum PBUFFER_TEXTURE_TYPE
		{
			PBUFFER_TEXTURE_TYPE_BRIGHTNESS = 0,
			PBUFFER_TEXTURE_TYPE_LOWRES,
			PBUFFER_TEXTURE_TYPE_LENSFLARE,
			PBUFFER_NUM_TEXTURES
		};

		pbuffer(void);
		virtual ~pbuffer(void);

		bool Init(int rX, int rY);

		void startFrame(void) const;
		void prepareAttachments(void) const;
		void drawForLensflare(void) const;

		void BindBrightnessTex(void) const;
		void BindLowResTex(void) const;
		void BindLensFlareTex(void) const;

		int ResolutionX, ResolutionY;

	protected:
		GLuint m_fbo;
		GLuint m_textures[PBUFFER_NUM_TEXTURES];
		GLuint generateAttachmentTexture(void);
	};
}

#endif


