#include "TransformationC.h"
#include "Entity.h"

namespace pp
{
	TransformationC::TransformationC(void) : 
		Component(TRANSFORMATION), 
		childCount(0), 
		parent(nullptr),
		hasChange(false),
		oldposy(0.f)
	{
		translationMat4.SetToIdentity();
		localtranslationMat4.SetToIdentity();
		scaleMat4.SetToIdentity();
		scale.Set(1.f, 1.f, 1.f);
		mat4Stack.LoadIdentity();
		localPosition.SetZero();
	}

	TransformationC::~TransformationC(void)
	{
	}

	void TransformationC::update(const float& dt)
	{
		// the owner must be active .. so is the updateflag
		if (getOwner()->isActive() && updatedFlag)
		{
			// check whether got parent or not
			if ( parent == nullptr && getOwner()->getParent() )
			{
				parent = getOwner()->getParent()->transformC;
			}

			TranslationMatUpdate();
			QuaternionRotationUpdate();
			ScaleMatUpdate();

			FinalMatrix = mat4Stack.Top() * translationMat4 * rotationQ.convertTomat4() * scaleMat4;

			LocalTranslationMatUpdate();

			if (parent)
			{
				// i only want rotation y only
				FinalMatrix = parent->localtranslationMat4 * parent->rotationQ.convertTomat4() * FinalMatrix;
				LocalTranslationMatUpdate();
			}

			// if have children .. rmb to ask them to update also .. because parent update finish le
			for (auto & c : getOwner()->children)
			{
				c->transformC->updatedFlag = true;
			}

			// matrix stack clear pls
			mat4Stack.Clear();

			// reset to false
			updatedFlag = false;
			hasChange = true;
		}
		
	}

	void TransformationC::TranslationMatUpdate(void)
	{
		translationMat4.SetToIdentity();
		translationMat4.SetToTranslation(position.x, position.y, position.z);
	}

	static void WragDeg(float& t)
	{
		while (t >= 360) t -= 360;
		while (t < 0) t += 360;
	}

	void TransformationC::QuaternionRotationUpdate(void)
	{
		WragDeg(rotation.x); WragDeg(rotation.y); WragDeg(rotation.z);

		Quaternion qx(rotation.x, vec3f(1, 0, 0));
		Quaternion qy(rotation.y, vec3f(0, 1.f, 0));
		Quaternion qz(rotation.z, vec3f(0, 0, 1.f));

		// rotate z first, then y, lastly z
		rotationQ = specialDragonRotate * rotationDiagonal * qz * qy * qx;
	}

	void TransformationC::ScaleMatUpdate(void)
	{
		scaleMat4.SetToIdentity();
		scaleMat4.SetToScale(scale.x, scale.y, scale.z);
	}

	void TransformationC::LocalTranslationMatUpdate(void)
	{
		localPosition = vec3f(FinalMatrix.a[12], FinalMatrix.a[13], FinalMatrix.a[14]);
		localtranslationMat4.SetToIdentity();
		localtranslationMat4.SetToTranslation(localPosition.x, localPosition.y, localPosition.z);
	}


	void TransformationC::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.getTransform.setPosition(" << guid << ", " << position << ") \n";
		myFile << "Entity.getTransform.setRotation(" << guid << ", " << rotation << ") \n";
		myFile << "Entity.getTransform.setScale(" << guid << ", " << scale << ") \n";
	}

	// Applies a rotation for each frame
	void TransformationC::Rotate(const vec3f& axis)
	{
		rotation += axis;

		updatedFlag = true;
	}

	// Rotates the transform about axis passing through point in world coordinates by angle degrees.
	void TransformationC::RotateAround(const vec3f& point, const vec3i& axis, const float& angle)
	{
		// do nothing 
	}

	// multiply another rotation mat
	void TransformationC::pushRotation(const float & angle, const vec3f & axis)
	{
		mat4Stack.PushMatrix();
		mat4Stack.QuaternionRotate(angle, axis);

		updatedFlag = true;
	}

	// Moves the transform in the direction and distance of translation.
	void TransformationC::Translate(const vec3f& translation)
	{
		if (!translation.IsZero())
		{
			// translate the positon vec
			position += translation;

			updatedFlag = true;
		}
	}

	void TransformationC::Scale(const vec3f& scale)
	{
		// scale the
		this->scale += scale;

		updatedFlag = true;
	}

	// Rotates the transform so the forward vector points at /target/'s current position.
	void TransformationC::LookAt(const vec3f& target)
	{
		vec3f dir = target - localPosition;
		dir.normalize();

		float parentRY = 0.f;
		if (parent)
			parentRY = parent->rotation.y;

		rotation.y = RadianToDegree(atan2(dir.x, dir.z)) - parentRY;

		updatedFlag = true;

		lookingDir = dir;
	}

	void TransformationC::LookAt(const vec3f& dir, const int& overload)
	{
		float parentRY = 0.f;
		if (parent)
			parentRY = parent->rotation.y;

		rotation.y = RadianToDegree(atan2(dir.x, dir.z)) - parentRY;

		updatedFlag = true;

		lookingDir = dir;
	}

	float isNegative(float v)
	{
		return v > 0 ? -1.f : 1.f;
	}

	void TransformationC::LookAtUp(const vec3f & dir, const int & overload)
	{
		if (!dir.IsZero())
		{
			vec3f A = dir;
			vec3f B = A;
			B.y = 0.f;

			float dotProduct = A.dot(B);
			float MULTAB = A.length() * B.length();

			float radian = acos(dotProduct / MULTAB); 
			if (radian == radian)
				rotation.x = RadianToDegree(radian) * isNegative(dir.y);

			updatedFlag = true;
		}

		else
		{
			rotation.x = 0.f;
		}
	}

	void TransformationC::LookAtAll(const vec3f & dir, const int & overload)
	{
		

		if ((dir.x == 0.f && dir.z == 0.f) || dir.IsZero())
		{
		}
		else
		{
			// rotate left and right
			LookAt(dir, 1);

			// finding the up and down angle
			vec3f up(0, 1.f, 0); // by default
			vec3f right = up.cross(dir);
			right.y = 0;
			right.normalize();

			float angle = 0.f;
			vec3f A = dir;
			vec3f B = A;
			B.y = 0.f;

			float dotProduct = A.dot(B);
			float MULTAB = A.length() * B.length();
			float radian = acos(dotProduct / MULTAB);
			if (radian == radian)
				angle = RadianToDegree(radian) * isNegative(dir.y);
			

			rotationDiagonal.setup(angle, right);

			updatedFlag = true;
		}
	}



	void TransformationC::PushLookAt(const vec3f& target)
	{
		if (parent)
		{
			vec3f dir = target - parent->localPosition;
			dir.normalize();

			pushRotation(RadianToDegree(atan2(dir.x, dir.z)) - parent->rotation.y, vec3f(0, 1, 0));
		}
	}

	void TransformationC::PushLookAt(const vec3f& dir, const int& overload)
	{
		if (parent)
		{
			pushRotation(RadianToDegree(atan2(dir.x, dir.z)) - parent->rotation.y, vec3f(0, 1, 0));
		}
	}

	// always facing the camera
	void TransformationC::LookAtCamera(const mat4f & view)
	{
		FinalMatrix.a[0] = view.a[0];
		FinalMatrix.a[1] = view.a[4];
		FinalMatrix.a[2] = view.a[8];

		FinalMatrix.a[4] = view.a[1];
		FinalMatrix.a[5] = view.a[5];
		FinalMatrix.a[6] = view.a[9];

		FinalMatrix.a[8] = view.a[2];
		FinalMatrix.a[9] = view.a[6];
		FinalMatrix.a[10] = view.a[10];
	}

	// get the final matrix
	mat4f& TransformationC::getFinalMat4(void)
	{
		return FinalMatrix;
	}

	// get the prev MVP matrix
	mat4f& TransformationC::getPrevMVPMat4(void)
	{
		return prevMVPMatrix;
	}

	void TransformationC::updatePrevMat4(const mat4f & prevView, const mat4f& prevProj)
	{
		this->prevMVPMatrix = prevProj *prevView * FinalMatrix;
	}
}
