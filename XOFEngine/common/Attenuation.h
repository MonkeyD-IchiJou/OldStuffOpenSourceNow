#ifndef ATTENUATION
#define ATTENUATION

namespace pp
{
	class Attenuation
	{
	public:
		Attenuation();
		Attenuation( float constant, float linear, float quadratic );
		virtual ~Attenuation();

		Attenuation& operator=(const Attenuation& rhs); //Assignment operator

		float constant;
		float linear;
		float quadratic;
	};
}

#endif

