#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "MathsHeader.h"
#include <vector>
#include "enumc.h"

namespace pp
{
	class Entity;
	class TransformationC;
	class DebugMesh;
	class debugShader;
	class PlayerManager;

	class Collectable
	{
	public:
		Collectable(void);
		~Collectable(void);

		void create(void);
		void draw(void) const;
		void add(const vec3f& pos);
		void update(const float &dt);
		void lateUpdate(const float &dt);
		void destroy(void);

	private:
		Entity* collectables;
		TransformationC* transformation;

		std::vector <mat4f> tmatrix;
		static DebugMesh* collectableMesh;

		static debugShader* shader;

		PlayerManager* p;
	};

}

#endif

