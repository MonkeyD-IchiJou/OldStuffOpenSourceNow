#include "quat4.h"
#include "quat4.h"
#include "MyMath.h"

namespace Math
{
	Quaternion::Quaternion(void)
	{
		w = 1;
	}

	Quaternion::Quaternion(float a, const vec3f& n)
	{
		a = DegreeToRadian(a);

		// rmb .. if w == 1, no rotation at all .. because user input a == 0 .. cos (0) is always 1;
		w = cos(a / 2);

		if (Math::FAbs(w) < EPSILON)
			w = 0;

		v = n*sin(a / 2);
	}

	void Quaternion::setup(float a, const vec3f & n)
	{
		a = DegreeToRadian(a);

		// rmb .. if w == 1, no rotation at all .. because user input a == 0 .. cos (0) is always 1;
		w = cos(a / 2);

		if (Math::FAbs(w) < EPSILON)
			w = 0;

		v = n*sin(a / 2);
	}

	const Quaternion Quaternion::Inverted() const
	{
		Quaternion q;
		q.w = w;
		q.v = -v;

		return q;
	}


	const Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		// Multiplying two quaternions together combines the rotation
		Quaternion r;

		r.w = w*q.w - v.dot(q.v);
		r.v = v*q.w + q.v*w + v.cross(q.v);

		return r;
	}

	// Rotate a vector with this quaternion.
	// The basic equation is qpq* (the * means inverse) but we use a simplified version of that equation. for right hand rule .. is q*pq
	const vec3f Quaternion::operator*(const vec3f& V) const
	{
		vec3f vcV = v.cross(V);
		vec3f returnVec = V + vcV*(2 * w) + v.cross(vcV) * 2;
		return returnVec;
	}

	float Quaternion::length(void) const
	{
		return sqrt(v.lengthSquared() + (w * w));
	}

	Quaternion Quaternion::normalized(void) const 
	{
		float d = length();

		if (d <= EPSILON && -d <= EPSILON)
			throw 0;

		Quaternion tq;

		tq.w = this->w / d;
		tq.v.x = this->v.x / d;
		tq.v.y = this->v.y / d;
		tq.v.z = this->v.z / d;

		return tq;
	}

	Quaternion& Quaternion::Normalize(void) 
	{
		float d = length();

		if (d <= EPSILON && -d <= EPSILON)
			throw 0;

		w /= d;
		v.x /= d;
		v.y /= d;
		v.z /= d;
		return *this;
	}

	mat4f Quaternion::convertTomat4(void)
	{
		Quaternion nq = this->Normalize();

		float qw = nq.w;
		float qx = nq.v.x;
		float qy = nq.v.y;
		float qz = nq.v.z;

		float n = qw * qw + qx * qx + qy * qy + qz * qz;

		mat4f qMtx;
		qMtx.a[0] = 1.0f - (2.0f*qy*qy) - (2.0f*qz*qz);
		qMtx.a[1] = (2.0f*qx*qy) + (2.0f*qz*qw);
		qMtx.a[2] = (2.0f*qx*qz) - (2.0f*qy*qw);
		qMtx.a[3] = 0.0f;

		qMtx.a[4] = (2.0f*qx*qy) - (2.0f*qz*qw);
		qMtx.a[5] = 1.0f - (2.0f*qx*qx) - (2.0f*qz*qz);
		qMtx.a[6] = (2.0f*qy*qz) + (2.0f*qx*qw);
		qMtx.a[7] = 0.0f;

		qMtx.a[8] = (2.0f*qx*qz) + (2.0f*qy*qw); 
		qMtx.a[9] = (2.0f*qy*qz) - (2.0f*qx*qw); 
		qMtx.a[10] = 1.0f - (2.0f*qx*qx) - (2.0f*qy*qy);
		qMtx.a[11] = 0.0f;

		return qMtx;
	}

	void Quaternion::ToAxisAngle(vec3f& vecAxis, float& flAngle) const
	{
		// Convert the quaternion back into axis/angle
		if (v.lengthSquared() < 0.0001f)
		{
			vecAxis = vec3f(1, 0, 0);
		}
		else
		{
			vecAxis = v.normalized();
		}

		// This is the opposite procedure as explained in
		// w = cos(a/2) and a = acos(w)*2
		flAngle = acos(w) * 2;

		// Convert to degrees
		flAngle = Math::RadianToDegree(flAngle);
	}

	Quaternion::~Quaternion(void)
	{
	}
}