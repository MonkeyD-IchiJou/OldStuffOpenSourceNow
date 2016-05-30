#ifndef FINALFBO_H
#define FINALFBO_H

#include "GLH.h"

namespace pp
{
	class finalFBO
	{
	public:
		finalFBO(void);
		~finalFBO(void);
		
		void Init(int SCR_WIDTH, int SCR_HEIGHT);

		void prepareMotionBlurPass(void) const;
		void prepareFinalPass(void) const;

		void bindMotionBlurTex(void) const;
		void bindFinalTex(void) const;

		int ResolutionX, ResolutionY;

	private:
		GLuint ppFBO;
		GLuint m_motionblurtex, m_finalTex;
	};
}

#endif

