#ifndef VEC4_H
#define VEC4_H

#include "utils.h"
#include <sstream>

namespace Math
{
	template<typename T>
	class vec4
	{
	public:
		T x, y, z, w;

		// constructor
		inline vec4(T x = 0, T y = 0, T z = 0, T w = 0) : x(x), y(y), z(z), w(0)
		{
		}

		// copy constructor
		inline vec4(const vec4 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
		{
		}

		// destructor
		inline ~vec4(void)
		{
		}

		// set up
		inline void Set(T a = 0, T b = 0, T c = 0, T d = 0)
		{
			x = a;
			y = b;
			z = c;
			w = d;
		}

		//Set all data to zero
		inline void SetZero(void)
		{
			x = y = z = w = 0;
		}

		//Check if data is zero
		bool IsZero(void) const
		{
			return IsEqual(x, x - x) && IsEqual(y, y - y) && IsEqual(z, z - z) && IsEqual(w, w - w);
		}

		//Vector addition
		inline vec4 operator+(const vec4& rhs) const
		{
			return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		inline vec4& operator+=(const vec4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		//Vector subtraction
		inline vec4 operator-(const vec4& rhs) const
		{
			return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		inline vec4& operator-=(const vec4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		//Vector multiplication
		inline vec4 operator*(const vec4& rhs) const
		{
			return vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		//Unary negation
		inline vec4 operator-(void) const
		{
			return vec4(-x, -y, -z, -w);
		}

		//Scalar multiplication
		inline vec4 operator*(float scalar) const
		{
			return vec4(scalar * x, scalar * y, scalar * z, scalar * w);
		}

		inline vec4& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		//Equality check
		bool operator==(const vec4& rhs) const
		{
			return IsEqual(x, rhs.x) && IsEqual(y, rhs.y) && IsEqual(z, rhs.z) && IsEqual(w, rhs.w);
		}

		//Inequality check
		bool operator!= (const vec4& rhs) const
		{
			return !IsEqual(x, rhs.x) || !IsEqual(y, rhs.y) || !IsEqual(z, rhs.z) || !IsEqual(w, rhs.w);
		}

		//Assignment operator
		inline vec4& operator=(const vec4& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		//Get magnitude
		inline T length(void) const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		//Get square of magnitude
		inline T lengthSquared(void) const
		{
			return x * x + y * y + z * z + w * w;
		}

		//Return a copy of this vector, normalized
		inline vec4 normalized(void) const 
		{
			T d = length();
			if (d <= EPSILON && -d <= EPSILON)
			{
				return vec4();
			}
			return vec4(x / d, y / d, z / d, w / d);
		}

		//Normalize this vector and return a reference to it
		inline vec4& normalize(void)
		{
			T d = length();
			if (d <= EPSILON && -d <= EPSILON)
			{
				*this = 0;
				return *this;
			}

			x /= d;
			y /= d;
			z /= d;
			w /= d;
			return *this;
		}

		//print to ostream
		friend std::ostream& operator<<(std::ostream& os, vec4& rhs)
		{
			os << "[ " << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << " ]";
			return os;
		}

		friend vec4 operator*(float scalar, const vec4& rhs)
		{
			return rhs * scalar;
		}

	private:
		// helper function to check equality (float type)
		bool IsEqual(float a, float b) const
		{
			return a - b <= EPSILON && b - a <= EPSILON;
		}

		// helper function to check equality (int type)
		bool IsEqual(int a, int b) const
		{
			return a - b <= 0 && b - a <= 0;
		}

		// helper function to check equality (double type)
		bool IsEqual(double a, double b) const
		{
			return a - b <= 0.0001 && b - a <= 0.0001;
		}

	};
	
	// shortcut name
	typedef vec4<int> vec4i;
	typedef vec4<float> vec4f;
	typedef vec4<double> vec4d;
}

#endif
