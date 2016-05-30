#ifndef PING_PONG_FBO_H
#define PING_PONG_FBO_H

#include "GLH.h"

namespace pp
{
	class pingpongFBO
	{
	public:
		pingpongFBO(void);
		~pingpongFBO(void);

		void Init(const int& rX, const int& rY);
		void clear(void);

		void viewPortUpdate(void)const;
		void bindFBO(const GLuint& i) const;
		void bindTex(const GLenum& active, const GLuint& i) const;

		int ResolutionX, ResolutionY;

	private:
		GLuint ppFBO[2];
		GLuint ppColorbuffers[2];
	};
}

#endif


