#ifndef BASIC_MESH_H
#define BASIC_MESH_H

#include <Importer.hpp>      // C++ importer interface
#include <scene.h>       // Output data structure
#include <postprocess.h> // Post processing flags
#include "Vertex.h"
#include "Mesh.h"

namespace pp
{
	class BasicMesh : public Mesh
	{
	public:
		BasicMesh(void);
		virtual ~BasicMesh(void);

		// load the mesh
		bool LoadMesh(const std::string &filename) override;

		// render with vao binding
		void Render(void) override;

		// render without binding
		void RenderWithoutBind(void) override;

	protected:
		bool InitFromScene(const aiScene* pScene);

		void InitMesh(const aiMesh* paiMesh,
			std::vector<Vertex>& vertex_buffer_data,
			std::vector<unsigned int>& index_buffer_data);


		std::vector<BasicMeshEntry> m_Entries;
	};
}

#endif


