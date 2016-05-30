#include "MatrixStack.h"

namespace Math
{
	MS::MS() {
		mat4f mat;
		mat.SetToIdentity();
		ms.push(mat);
	}

	MS::~MS() {
	}

	const mat4f& MS::Top() const {
		return ms.top();
	}

	void MS::PopMatrix() {
		ms.pop();
	}

	void MS::PushMatrix() {
		ms.push(ms.top());
	}

	void MS::Clear() {
		while (ms.size() > 1)
			ms.pop();
	}

	void MS::LoadIdentity() {
		mat4f mat;
		mat.SetToIdentity();
		ms.top() = mat;
	}

	void MS::LoadMatrix(const mat4f &matrix) {
		ms.top() = matrix;
	}

	void MS::MultMatrix(const mat4f &matrix) {
		ms.top() = ms.top() * matrix;
	}

	void MS::QuaternionRotate(const float& w, const vec3f& v)
	{
		mat4f mat;
		Quaternion q = Quaternion(w, v);
		mat = q.convertTomat4();
		ms.top() = ms.top() * mat;
	}

	void MS::Scale(const vec3f& scale)
	{
		mat4f mat;
		mat.SetToScale(scale.x, scale.y, scale.z);
		ms.top() = ms.top() * mat;
	}

	void MS::Translate(const vec3f& translation)
	{
		mat4f mat;
		mat.SetToTranslation(translation.x, translation.y, translation.z);
		ms.top() = ms.top() * mat;
	}
	
}
