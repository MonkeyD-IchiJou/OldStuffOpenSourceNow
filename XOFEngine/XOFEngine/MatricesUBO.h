#ifndef MATRICES_UBO_H
#define MATRICES_UBO_H

#include "UBO.h"

namespace pp
{
	class MatricesUBO : public UBO
	{
	public:
		MatricesUBO(void);
		virtual ~MatricesUBO(void);

		void create(void) override;
		void updateALL(const mat4f& view, const mat4f& projection);
		void load_ViewMatrix(const mat4f& view);
		void load_ProjectionMatrix(const mat4f& projection);
	};
}

#endif


