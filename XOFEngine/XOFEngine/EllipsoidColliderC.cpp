#include "EllipsoidColliderC.h"
#include "Entity.h"
#include "TransformationC.h"
#include "Mesh.h"

#include "ShaderHeaven.h"
#include "commonShader.h"


#include "ModelLibrary.h"

namespace pp
{
	commonShader* EllipsoidColliderC::shader = nullptr;
	Mesh* EllipsoidColliderC::sphere = nullptr;

	EllipsoidColliderC::EllipsoidColliderC(void) :
		ColliderC(ELLIPSOID_TYPE),
		foundCollision(false),
		foundCollisionGravity(false),
		gravitySliding(false),
		nearestDistance(0.0),
		modelMatrix(nullptr),
		transform(nullptr),
		collisionRecursionDepth(0),
		isSliding(false)
	{
		eRadius.Set(1.f, 1.f, 1.f);
		R3gravity.Set(0, 0.f, 0);

		if (sphere == nullptr)
		{
			sphere = ModelLibrary::getInstance()->models["SPHERE"];
		}

		if (shader == nullptr)
			shader = ShaderHeaven::getInstance()->commonshader;
	}


	EllipsoidColliderC::~EllipsoidColliderC(void)
	{
	}

	void EllipsoidColliderC::update(const float& dt)
	{
		if (getOwner()->isActive())
		{
			if (updatedFlag)
			{
				if (transform == nullptr) transform = getOwner()->transformC;

				// get the handle for model matrix
				if (modelMatrix == nullptr) modelMatrix = &transform->translationMat4;
				
				updatedFlag = false;
			}
		}
	}

	void EllipsoidColliderC::draw(void) const
	{
		if (getOwner()->isActive())
		{
			if (modelMatrix)
			{
				mat4f scale;
				scale.SetToIdentity();
				scale.SetToScale(eRadius.x, eRadius.y, eRadius.z);
				// draw the ellipsoid sphere
				shader->load_ModelMatrix(*modelMatrix * scale);
				sphere->Render();
			}
		}
	}

	void EllipsoidColliderC::save(ofstream& myFile, const unsigned int & guid)
	{

	}

	void EllipsoidColliderC::updateNormalizeVelocity(void)
	{
		normalizedVelocity = velocity;
		if (!normalizedVelocity.IsZero())
		{
			normalizedVelocity.normalize();
		}
		else
		{
			normalizedVelocity.SetZero();
		}
	}
	void EllipsoidColliderC::updateR3PosAndVel(void)
	{
		if(transform)
			R3Position = transform->position;
	}
	void EllipsoidColliderC::updateFinalPos(const vec3f & pos)
	{
		if (transform)
		{
			transform->position = pos;
			transform->updatedFlag = true;
		}
	}
	void EllipsoidColliderC::checkIsSliding(void)
	{
		if (OldDestinationPointGravity.y < newDestinationPointGravity.y)
		{
			isSliding = false;
		}
		else if (OldDestinationPointGravity.y > newDestinationPointGravity.y)
		{
			if(!R3slidingDir.IsZero())
				isSliding = true;
		}
	}
	void EllipsoidColliderC::lockDestinationPoint(void)
	{
		OldDestinationPointGravity.y = newDestinationPointGravity.y;
	}
}

