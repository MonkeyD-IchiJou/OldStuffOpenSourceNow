#ifndef DEPTHMAPFBO_H
#define DEPTHMAPFBO_H

#include "GLH.h"

namespace pp
{
	class depthMapFBO
	{
	public:
		depthMapFBO();
		~depthMapFBO();

		void Init(int SCR_WIDTH, int SCR_HEIGHT);
		void prepareForDrawing(void) const;
		void bindDepthMap(const GLenum& active) const;
		void clear(void);

		int ResolutionX, ResolutionY;

	private:
		GLuint depthFBO;
		GLuint depthMap;
	};
}

#endif

