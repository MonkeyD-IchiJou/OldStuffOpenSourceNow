#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "ColliderC.h"

#include "MathsHeader.h"

#include <vector>

namespace pp
{
	class commonShader;
	class Mesh;
	class TransformationC;

	class EllipsoidColliderC :
		public ColliderC
	{
	public:
		EllipsoidColliderC(void);
		virtual ~EllipsoidColliderC(void);

		void update(const float& dt) override;
		void draw(void) const override;
		void save(ofstream& myFile, const unsigned int & guid) override;

	public:

		/*all variables*/

		vec3f eRadius; // ellipsoid radius

		// Information about the move being requested: (in eSpace)
		vec3f velocity;
		vec3f normalizedVelocity;
		vec3f basePoint;

		// Information about the move being requested: (in R3)
		vec3f R3Velocity;
		vec3f R3Attack;
		vec3f R3gravity;
		vec3f R3Position;

		// Hit information
		bool foundCollision;
		bool foundCollisionGravity;
		bool gravitySliding;
		double nearestDistance;
		vec3f intersectionPoint;
		vec3f R3slidingDir;

		vec3f newDestinationPointGravity;
		vec3f OldDestinationPointGravity;

		bool isSliding;

		int collisionRecursionDepth;

		inline vec3f espaceV(void) { return vec3f(1.f / eRadius.x, 1.f / eRadius.y, 1.f / eRadius.z); };
		void updateNormalizeVelocity(void);
		void updateR3PosAndVel(void);
		void updateFinalPos(const vec3f& pos);

		void checkIsSliding(void);
		void lockDestinationPoint(void);


	private:
		static commonShader* shader;

		// for hitbox 
		static Mesh* sphere;

		// owner final model matrix
		mat4f* modelMatrix;

		TransformationC* transform; 

		
	};
}


#endif

