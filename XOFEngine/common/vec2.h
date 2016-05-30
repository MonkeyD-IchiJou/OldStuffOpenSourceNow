#ifndef VEC2_H
#define VEC2_H

#include "utils.h"
#include <ostream>

namespace Math
{
	template<typename T>
	class vec2
	{
	public:
		T x, y;

		// constructor
		inline vec2(T x = 0, T y = 0) : x(x), y(y)
		{
		}

		// copy constructor
		inline vec2(const vec2 &rhs) : x(rhs.x), y(rhs.y)
		{
		}

		// destructor
		inline ~vec2(void)
		{
		}

		// set up
		inline void Set(T a = 0, T b = 0)
		{
			x = a;
			y = b;
		}

		//Set all data to zero
		inline void SetZero(void)
		{
			x = y = 0;
		}

		//Check if data is zero
		bool IsZero(void) const
		{
			return IsEqual(x, x - x) && IsEqual(y, y - y);
		}

		//Vector addition
		inline vec2 operator+(const vec2& rhs) const
		{
			return vec2(x + rhs.x, y + rhs.y);
		}

		inline vec2& operator+=(const vec2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		//Vector subtraction
		inline vec2 operator-(const vec2& rhs) const
		{
			return vec2(x - rhs.x, y - rhs.y);
		}

		inline vec2& operator-=(const vec2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		//Vector multiplication
		inline vec2 operator*(const vec2& rhs) const
		{
			return vec2(x * rhs.x, y * rhs.y);
		}

		//Unary negation
		inline vec2 operator-(void) const
		{
			return vec2(-x, -y);
		}

		//Scalar multiplication
		inline vec2 operator*(float scalar) const
		{
			return vec2(scalar * x, scalar * y);
		}

		inline vec2& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		//Equality check
		bool operator==(const vec2& rhs) const
		{
			return IsEqual(x, rhs.x) && IsEqual(y, rhs.y);
		}

		//Inequality check
		bool operator!= (const vec2& rhs) const
		{
			return !IsEqual(x, rhs.x) || !IsEqual(y, rhs.y);
		}

		//Assignment operator
		inline vec2& operator=(const vec2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		//Get magnitude
		inline T length(void) const
		{
			return sqrt(x * x + y * y);
		}

		//Get square of magnitude
		inline T lengthSquared(void) const
		{
			return x * x + y * y ;
		}

		//dot product
		inline T dot(const vec2& rhs) const
		{
			return ((x * rhs.x) + (y * rhs.y));
		}

		//Return a copy of this vector, normalized
		inline vec2 normalized(void) const
		{
			T d = length();
			if (d <= EPSILON && -d <= EPSILON)
			{
				return vec2();
			}
			return vec2(x / d, y / d);
		}

		//Normalize this vector and return a reference to it
		inline vec2& normalize(void)
		{
			T d = length();
			if (d <= EPSILON && -d <= EPSILON)
			{
				*this = 0;
				return *this;
			}

			x /= d;
			y /= d;
			return *this;
		}

		//print to ostream
		friend std::ostream& operator<<(std::ostream& os, vec2& rhs)
		{
			os << rhs.x << ", " << rhs.y;
			return os;
		}

		friend vec2 operator*(float scalar, const vec2& rhs)
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
	typedef vec2<int> vec2i;
	typedef vec2<float> vec2f;
	typedef vec2<double> vec2d;
}

#endif
