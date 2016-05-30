#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"
#include "MyMath.h"

namespace Math
{
	template<typename T>
	class mat4
	{
	public:
		T a[16];

		inline mat4(
			T a00 = 1, T a10 = 0, T a20 = 0, T a30 = 0, 
			T a01 = 0, T a11 = 1, T a21 = 0, T a31 = 0, 
			T a02 = 0, T a12 = 0, T a22 = 1, T a32 = 0, 
			T a03 = 0, T a13 = 0, T a23 = 0, T a33 = 1)
		{
			a[0] = a00;		a[4] = a01;     a[8] = a02;			a[12] = a03;
			a[1] = a10;		a[5] = a11;		a[9] = a12;			a[13] = a13;
			a[2] = a20;		a[6] = a21;		a[10] = a22;		a[14] = a23;
			a[3] = a30;		a[7] = a31;		a[11] = a32;		a[15] = a33;
		}

		inline mat4(const T m[16])
		{
			for (int i = 0; i < 16; i++)
			{
				a[i] = m[i];
			}
		}

		inline mat4(const mat4 &rhs)
		{
			for (int i = 0; i < 16; i++)
			{
				a[i] = rhs.a[i];
			}
		}

		inline void SetToIdentity(void)
		{
			SetToZero();
			a[0] = a[5] = a[10] = a[15] = static_cast<T>(1);
		}

		inline void Transpose(void)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = i + 1; j < 4; j++)
				{
					swap(a[i * 4 + j], a[j * 4 + i]);
				}
			}
		}

		inline void SetToZero(void)
		{
			for (int i = 0; i < 16; i++)
			{
				a[i] = 0;
			}
		}

		inline mat4 GetTranspose() const
		{
			mat4 ret(*this);
			ret.Transpose();
			return ret;
		}

		inline mat4 GetInverse() const
		{
			float a0 = a[0] * a[5] - a[1] * a[4];
			float a1 = a[0] * a[6] - a[2] * a[4];
			float a2 = a[0] * a[7] - a[3] * a[4];
			float a3 = a[1] * a[6] - a[2] * a[5];
			float a4 = a[1] * a[7] - a[3] * a[5];
			float a5 = a[2] * a[7] - a[3] * a[6];
			float b0 = a[8] * a[13] - a[9] * a[12];
			float b1 = a[8] * a[14] - a[10] * a[12];
			float b2 = a[8] * a[15] - a[11] * a[12];
			float b3 = a[9] * a[14] - a[10] * a[13];
			float b4 = a[9] * a[15] - a[11] * a[13];
			float b5 = a[10] * a[15] - a[11] * a[14];

			float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

			if (abs(det) < EPSILON)
				throw 0;

			mat4 inverse;
			if (FAbs(det) > EPSILON)
			{
				inverse.a[0] = +a[5] * b5 - a[6] * b4 + a[7] * b3;
				inverse.a[4] = -a[4] * b5 + a[6] * b2 - a[7] * b1;
				inverse.a[8] = +a[4] * b4 - a[5] * b2 + a[7] * b0;
				inverse.a[12] = -a[4] * b3 + a[5] * b1 - a[6] * b0;
				inverse.a[1] = -a[1] * b5 + a[2] * b4 - a[3] * b3;
				inverse.a[5] = +a[0] * b5 - a[2] * b2 + a[3] * b1;
				inverse.a[9] = -a[0] * b4 + a[1] * b2 - a[3] * b0;
				inverse.a[13] = +a[0] * b3 - a[1] * b1 + a[2] * b0;
				inverse.a[2] = +a[13] * a5 - a[14] * a4 + a[15] * a3;
				inverse.a[6] = -a[12] * a5 + a[14] * a2 - a[15] * a1;
				inverse.a[10] = +a[12] * a4 - a[13] * a2 + a[15] * a0;
				inverse.a[14] = -a[12] * a3 + a[13] * a1 - a[14] * a0;
				inverse.a[3] = -a[9] * a5 + a[10] * a4 - a[11] * a3;
				inverse.a[7] = +a[8] * a5 - a[10] * a2 + a[11] * a1;
				inverse.a[11] = -a[8] * a4 + a[9] * a2 - a[11] * a0;
				inverse.a[15] = +a[8] * a3 - a[9] * a1 + a[10] * a0;

				float invDet = 1.f / det;
				inverse.a[0] *= invDet;
				inverse.a[1] *= invDet;
				inverse.a[2] *= invDet;
				inverse.a[3] *= invDet;
				inverse.a[4] *= invDet;
				inverse.a[5] *= invDet;
				inverse.a[6] *= invDet;
				inverse.a[7] *= invDet;
				inverse.a[8] *= invDet;
				inverse.a[9] *= invDet;
				inverse.a[10] *= invDet;
				inverse.a[11] *= invDet;
				inverse.a[12] *= invDet;
				inverse.a[13] *= invDet;
				inverse.a[14] *= invDet;
				inverse.a[15] *= invDet;
			}
			return inverse;
		}

		inline mat4 operator*(const mat4& rhs) const
		{
			mat4 ret;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ret.a[i * 4 + j] = a[0 * 4 + j] * rhs.a[i * 4 + 0] + a[1 * 4 + j] * rhs.a[i * 4 + 1] + a[2 * 4 + j] * rhs.a[i * 4 + 2] + a[3 * 4 + j] * rhs.a[i * 4 + 3];
				}
			}

			return ret;
		}

		inline mat4 operator+(const mat4& rhs) const
		{

		}

		inline mat4& operator=(const mat4& rhs)
		{
			for (int i = 0; i < 16; i++)
			{
				a[i] = rhs.a[i];
			}
			return *this;
		}

		inline mat4 operator*(T scalar) const
		{

		}

		inline vec3f operator*(const vec3f& rhs) const
		{
			float b[4];
			for (int i = 0; i < 4; i++)
				b[i] = a[0 * 4 + i] * rhs.x + a[1 * 4 + i] * rhs.y + a[2 * 4 + i] * rhs.z + a[3 * 4 + i];
			vec3f ret(b[0], b[1], b[2]);
			return ret;
		}

		inline vec4f operator*(const vec4f& v) const
		{
			vec4f result;

			result.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12] * v.w;
			result.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13] * v.w;
			result.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14] * v.w;
			result.w = a[3] * v.x + a[7] * v.y + a[11] * v.z + a[15] * v.w;

			return result;
		}

		inline void SetToScale(T sx, T sy, T sz)
		{
			SetToIdentity();
			a[0] = sx;
			a[5] = sy;
			a[10] = sz;
		}

		inline void SetToTranslation(T tx, T ty, T tz)
		{
			SetToIdentity();
			a[12] = tx;
			a[13] = ty;
			a[14] = tz;
		}
		
		inline void SetToLookAt(const vec3f& eye,
			const vec3f& target,
			const vec3f& up)
		{
			vec3f zaxis = (eye - target).normalized();    // The "forward" vector.
			vec3f xaxis = (up.cross(zaxis)).normalized();// The "right" vector.
			vec3f yaxis = zaxis.cross(xaxis);     // The "up" vector.

			// Create a 4x4 view matrix from the right, up, forward and eye position vectors
			mat4 viewMatrix(
				xaxis.x, yaxis.x, zaxis.x, 0,
				xaxis.y, yaxis.y, zaxis.y, 0,
				xaxis.z, yaxis.z, zaxis.z, 0,
				-xaxis.dot(eye), -yaxis.dot(eye), -zaxis.dot(eye), 1);

			*this = viewMatrix;
		}

		inline void SetToPerspective(double fovy, double aspect, double zNear, double zFar)
		{
			double f = 1.0 / tan(PI / 180 * fovy / 2);
			*this = mat4((float)(f / aspect), 0, 0, 0,
				0, (float)f, 0, 0,
				0, 0, (float)((zFar + zNear) / (zNear - zFar)), -1.0f,
				0, 0, (float)(2 * zFar * zNear / (zNear - zFar)), 0);
		}

		inline void SetToOrtho(double left, double right, double bottom, double top, double nearVal, double farVal)
		{
			*this = mat4(2 / (float)(right - left), 0, 0, 0,
				0, 2 / (float)(top - bottom), 0, 0,
				0, 0, -2 / (float)(farVal - nearVal), 0,
				-(float)((right + left) / (right - left)), -(float)((top + bottom) / (top - bottom)), -(float)((farVal + nearVal) / (farVal - nearVal)), 1);
		}

	private:

		void swap(T &v1, T &v2)
		{
			T temp = v1;
			v1 = v2;
			v2 = temp;
		}
	};
	
	typedef mat4<float> mat4f;
	typedef mat4<int> mat4i;
	typedef mat4<double> mat4d;
}

#endif