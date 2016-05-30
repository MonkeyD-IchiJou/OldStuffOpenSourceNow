#ifndef MESH_H
#define MESH_H

#include "GLH.h"
#include <vector>

#include "vec3.h"
using namespace Math;

namespace pp
{
	struct BasicMeshEntry
	{
		BasicMeshEntry(void)
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
	};

	class Mesh
	{
	public:
		Mesh(void);
		virtual ~Mesh(void);

		// load the mesh
		virtual bool LoadMesh(const std::string &filename);
		virtual bool LoadMesh();

		virtual void Render(void) = 0;
		virtual void RenderWithoutBind(void) = 0;
		GLuint getIndexSize(void) const;
		void bindVertexArray(void) const;

		std::vector<vec3f > allTris;

	protected:
		void Clear(void);
		GLuint m_VAO;
		GLuint m_Buffers[2];
		GLuint IndexSize;
	};
}

#endif


