#include "AttenuationFormula.h"

namespace pp
{
	Attenuation * AttenuationFormula::attenuation = nullptr;
	AttenuationFormula::AttenuationFormula(void)
	{
		
	}


	AttenuationFormula::~AttenuationFormula(void)
	{
		
		
	}

	void AttenuationFormula::createFormula(void)
	{
		// once created .. no need to create anymore

		if (attenuation == nullptr)
		{
			attenuation = new Attenuation[12];

			// 7
			attenuation[0].constant = 1.0f;
			attenuation[0].linear = 0.7f;
			attenuation[0].quadratic = 1.8f;

			// 13
			attenuation[1].constant = 1.0f;
			attenuation[1].linear = 0.35f;
			attenuation[1].quadratic = 0.44f;

			// 20
			attenuation[2].constant = 1.0f;
			attenuation[2].linear = 0.22f;
			attenuation[2].quadratic = 0.20f;

			// 32
			attenuation[3].constant = 1.0f;
			attenuation[3].linear = 0.14f;
			attenuation[3].quadratic = 0.07f;

			// 50
			attenuation[4].constant = 1.0f;
			attenuation[4].linear = 0.09f;
			attenuation[4].quadratic = 0.032f;

			// 65
			attenuation[5].constant = 1.0f;
			attenuation[5].linear = 0.07f;
			attenuation[5].quadratic = 0.017f;

			// 100
			attenuation[6].constant = 1.0f;
			attenuation[6].linear = 0.045f;
			attenuation[6].quadratic = 0.0075f;

			// 160
			attenuation[7].constant = 1.0f;
			attenuation[7].linear = 0.027f;
			attenuation[7].quadratic = 0.0028f;

			// 200
			attenuation[8].constant = 1.0f;
			attenuation[8].linear = 0.022f;
			attenuation[8].quadratic = 0.0019f;

			// 325
			attenuation[9].constant = 1.0f;
			attenuation[9].linear = 0.014f;
			attenuation[9].quadratic = 0.0007f;

			// 600
			attenuation[10].constant = 1.0f;
			attenuation[10].linear = 0.007f;
			attenuation[10].quadratic = 0.0002f;

			attenuation[11].constant = 1.0f;
			attenuation[11].linear = 0.0014f;
			attenuation[11].quadratic = 0.000007f;
		}
	}

	void AttenuationFormula::destroyFormula(void)
	{
		if (attenuation != nullptr)
		{
			delete[]attenuation;
			attenuation = nullptr;
		}
	}

}
