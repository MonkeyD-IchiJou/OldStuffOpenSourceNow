#ifndef VEC3_H
#define VEC3_H

#include "utils.h"
#include <sstream>

namespace Math
{
	template<typename T>
	class vec3
	{
	public:
		T x, y, z;

		// constructor
		inline vec3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z)
		{
		}

		// copy constructor
		inline vec3(const vec3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
		{
		}

		// destructor
		inline ~vec3(void)
		{
		}

		// set up
		inline void Set(T a = 0, T b = 0, T c = 0)
		{
			x = a;
			y = b;
			z = c;
		}

		//Set all data to zero
		inline void SetZero(void)
		{
			x = y = z = 0;
		}

		//Check if data is zero
		bool IsZero(void) const
		{
			return IsEqual(x, x-x) && IsEqual(y, y-y) && IsEqual(z, z-z);
		}

		//Vector addition
		inline vec3 operator+(const vec3& rhs) const
		{
			return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		inline vec3& operator+=(const vec3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		//Vector subtraction
		inline vec3 operator-(const vec3& rhs) const
		{
			return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		inline T operator[](const int& d) const
		{
			if(d == 0) return this->x;
			else if(d == 1) return this->y;
			else if(d == 2) return this->z;
			
			return 0.f;
		}

		inline vec3& operator-=(const vec3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		//Vector multiplication
		inline vec3 operator*(const vec3& rhs) const
		{
			return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		//Unary negation
		inline vec3 operator-(void) const
		{
			return vec3(-x, -y, -z);
		}

		//Scalar multiplication
		inline vec3 operator*(float scalar) const
		{
			return vec3(scalar * x, scalar * y, scalar * z);
		}

		inline vec3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		//Equality check
		bool operator==(const vec3& rhs) const
		{
			return IsEqual(x, rhs.x) && IsEqual(y, rhs.y) && IsEqual(z, rhs.z);
		}

		//Inequality check
		bool operator!= (const vec3& rhs) const
		{
			return !IsEqual(x, rhs.x) || !IsEqual(y, rhs.y) || !IsEqual(z, rhs.z);
		}

		//Assignment operator
		inline vec3& operator=(const vec3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		//Get magnitude
		inline T length(void) const
		{
			return sqrt(x * x + y * y + z * z);
		}

		//Get square of magnitude
		inline T lengthSquared(void) const
		{
			return x * x + y * y + z * z;
		}

		//dot product
		inline T dot(const vec3& rhs) const
		{
			return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z));
		}

		//cross product
		inline vec3 cross(const vec3& rhs) const
		{
			return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		}

		//Return a copy of this vector, normalized
		inline vec3 normalized(void) const 
		{
			T d = length();
			if (d <= EPSILON && -d <= EPSILON)
			{
				return vec3();
			}
			return vec3(x / d, y / d, z / d);
		}

		//Normalize this vector and return a reference to it
		inline vec3& normalize(void)
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
			return *this;
		}

		//print to ostream
		friend std::ostream& operator<<(std::ostream& os, vec3& rhs)
		{
			os <<  rhs.x << ", " << rhs.y << ", " << rhs.z;
			return os;
		}

		friend vec3 operator*(float scalar, const vec3& rhs)
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
	typedef vec3<int> vec3i;
	typedef vec3<float> vec3f;
	typedef vec3<double> vec3d;
}

#endif
