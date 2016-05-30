#ifndef SKYBOX_BUFFER_H
#define SKYBOX_BUFFER_H

#include "GLH.h"

namespace pp
{

	class skyboxbuffer
	{
	public:
		skyboxbuffer(void);
		~skyboxbuffer(void);

		bool Init(const int &rX, const int &rY);
		void receiveBuff(void) const;
		void BindFinalTex(void) const;
		GLuint getFinaltexture(void) const;

		int ResolutionX, ResolutionY;

	private:
		void clear();

		GLuint m_fbo;
		GLuint rboDepth;
		GLuint m_textures;
	};
}

#endif
