#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Component.h"
#include "MatrixStack.h"
using namespace Math;

namespace pp
{
	class TransformationC :
		public Component
	{
	public:
		TransformationC(void);
		virtual ~TransformationC(void);

		void update(const float& dt) override;
		void save(ofstream& myFile, const unsigned int & guid) override;

		// Applies a rotation for each frame
		void Rotate(const vec3f& axis);

		// Rotates the transform about axis passing through point in world coordinates by angle degrees.
		void RotateAround(const vec3f& point, const vec3i& axis, const float& angle);

		// multiply another rotation mat
		void pushRotation(const float & angle, const vec3f & axis);

		// Moves the transform in the direction and distance of translation.
		void Translate(const vec3f& translation);

		void Scale(const vec3f& scale);

		// Rotates the transform so the forward vector points at /target/'s current position.
		void LookAt(const vec3f& target);
		void LookAt(const vec3f& dir, const int& overload);
		void LookAtUp(const vec3f& dir, const int& overload);
		void LookAtAll(const vec3f& dir, const int& overload);

		void PushLookAt(const vec3f& target);
		void PushLookAt(const vec3f& dir, const int& overload);

		// always facing the camera
		void LookAtCamera(const mat4f & view);

		// get the final matrix
		mat4f& getFinalMat4(void);

		// get the prev MVP matrix
		mat4f& getPrevMVPMat4(void);

		// update prev matrix for motion blur
		void updatePrevMat4(const mat4f & prevView, const mat4f& prevProj);

	public:
		// variables

		// the number of children the transform has
		int childCount;

		// position of the transform relative to the parent
		vec3f localPosition;

		// the rotation fo the transform relative to the parent transform's rotation
		vec4f localRotation;

		// the scale of the transform relative to the parent
		vec3f localScale;

		// Matrix that transforms a point from local space into world space (Read Only).
		mat4f localToWorldMatrix;

		// The parent of the transform.
		TransformationC *parent;

		// returns the topmost transform in the hierarchy
		TransformationC* root;

		// the positin of the transform in world space
		vec3f position;

		//The rotation of the transform in world space stored as a Quaternion.
		Quaternion rotationQ;

		Quaternion rotationDiagonal;

		Quaternion specialDragonRotate;

		// x : rotate around x axis .. so on ..
		vec3f rotation;

		// the scale baby
		vec3f scale;

		// translation and scale in matrix form 
		mat4f translationMat4, scaleMat4, localtranslationMat4;

		bool hasChange;

		float oldposy;

		vec3f lookingDir;

	private:

		// convert all the matrix
		// final transformation matrix that is kena push to shader de
		mat4f FinalMatrix;

		// prev MVP matrix
		mat4f prevMVPMatrix;

		// mat stack for extra transformation
		MS mat4Stack;

		void LocalTranslationMatUpdate(void);
		void TranslationMatUpdate(void);
		void ScaleMatUpdate(void);
		void QuaternionRotationUpdate(void);
	};
}

#endif
