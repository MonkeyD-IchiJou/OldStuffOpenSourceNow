#ifndef DEBUG_MESH_H
#define DEBUG_MESH_H

#include <Importer.hpp>      // C++ importer interface
#include <scene.h>       // Output data structure
#include <postprocess.h> // Post processing flags
#include "Vertex.h"
#include "Mesh.h"
#include <vector>
#include "mat4.h"

namespace pp
{
	class DebugMesh : public Mesh
	{
	public:
		DebugMesh(void);
		virtual ~DebugMesh(void);

		// load the mesh
		bool LoadMesh(const std::string &filename) override;

		void Render(void) override;
		void RenderWithoutBind(void) override;

		void RenderInstanced(std::vector<mat4f>& modelMatrices);
		void RenderInstancedTriangle(const std::vector<mat4f>& modelMatrices) ;

		GLuint instanceBuffer;

	private:
		bool InitFromScene(const aiScene* pScene);

		void InitMesh(const aiMesh* paiMesh,
			std::vector<vec3f>& vertex_buffer_data,
			std::vector<unsigned int>& index_buffer_data);

		std::vector<BasicMeshEntry> m_Entries;
	};
}

#endif


