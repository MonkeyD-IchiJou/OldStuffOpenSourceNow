#ifndef UBO_H
#define UBO_H

#include "GLH.h"
#include "mat4.h"

using namespace Math;

namespace pp
{
	class UBO
	{
	public:
		UBO(void);
		virtual ~UBO(void);

		virtual void create(void) = 0;
		void clear(void);

	protected:
		GLuint ubo;
	};
}

#endif


