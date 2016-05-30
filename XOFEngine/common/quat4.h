#ifndef QUATERNION_H
#define QUATERNION_H

#include "mat4.h"
#include "vec4.h"

namespace Math
{
	class Quaternion
	{
	public:
		float w;
		vec3f v;

		Quaternion(void);
		Quaternion(float a, const vec3f& n);
		void setup(float a, const vec3f& n);
		~Quaternion(void);

		const Quaternion Inverted() const;
		const Quaternion operator*(const Quaternion& q) const;
		const vec3f operator*(const vec3f& V) const;

		float length(void) const;
		Quaternion normalized(void) const;
		Quaternion& Normalize(void);

		// convert Quaternion to matrix
		mat4f convertTomat4(void);
		void ToAxisAngle(vec3f& vecAxis, float& flAngle) const;
	};
}

#endif

