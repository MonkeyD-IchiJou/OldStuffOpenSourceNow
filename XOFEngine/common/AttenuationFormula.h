#ifndef ATTENUATION_FORMULA_H
#define ATTENUATION_FORMULA_H

#include "Attenuation.h"

namespace pp
{
	class AttenuationFormula
	{
	public:
		AttenuationFormula(void);
		~AttenuationFormula(void);

		static void createFormula(void);
		static void destroyFormula(void);
		static Attenuation *attenuation;
	};
}
#endif

