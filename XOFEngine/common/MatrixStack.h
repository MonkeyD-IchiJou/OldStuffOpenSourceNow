#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <stack>
#include "quat4.h"

namespace Math
{
	class MS 
	{
	public:
		MS();
		~MS();
		const mat4f& Top() const;
		void PopMatrix();
		void PushMatrix();
		void Clear();
		void LoadIdentity();
		void LoadMatrix(const mat4f &matrix);
		void MultMatrix(const mat4f &matrix);
		void QuaternionRotate(const float& w, const vec3f& v);
		void Scale(const vec3f& scale);
		void Translate(const vec3f& translation);

	private:
		std::stack<mat4f> ms;
	};
}

#endif
