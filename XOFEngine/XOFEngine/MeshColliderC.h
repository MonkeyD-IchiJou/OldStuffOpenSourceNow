#ifndef MESH_COLLIDERC_H
#define MESH_COLLIDERC_H

#include "ColliderC.h"
#include "MathsHeader.h"

#include <vector>

namespace pp
{
	class Mesh;
	class commonShader;

	class MeshColliderC :
		public ColliderC
	{
	public:
		MeshColliderC(void);
		virtual ~MeshColliderC(void);

		void update(const float& dt) override;
		void draw(void) const override;
		void save(ofstream& myFile, const unsigned int & guid) override;

		inline std::string getMeshName(void) { return meshName; };
		inline void setMeshName(std::string name) { meshName = name; };

		std::vector<vec3f> tris;

	private:

		std::string meshName;

		static commonShader* shader;

		// owner final model matrix
		mat4f* modelMatrix;

		// for hitbox 
		Mesh* mesh;
	};
}

#endif


