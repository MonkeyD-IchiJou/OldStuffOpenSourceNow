#include "UBO.h"

namespace pp
{
	UBO::UBO(void) : ubo(0)
	{
	}

	UBO::~UBO(void)
	{
		clear();
	}

	void UBO::clear(void)
	{
		if (ubo != 0)
		{
			glDeleteBuffers(1, &ubo);
		}
	}

	
}