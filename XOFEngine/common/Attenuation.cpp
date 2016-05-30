#include "Attenuation.h"


namespace pp
{
	Attenuation::Attenuation() : constant(1.f), linear(0.09f), quadratic(0.032f)
	{
	}

	Attenuation::Attenuation(float constant, float linear, float quadratic) : constant(constant), linear(linear), quadratic(quadratic)
	{
	}


	Attenuation::~Attenuation(void)
	{
	}

	Attenuation & Attenuation::operator=(const Attenuation & rhs)
	{
		this->constant = rhs.constant;
		this->linear = rhs.linear;
		this->quadratic = rhs.quadratic;

		return *this;
	}
}
