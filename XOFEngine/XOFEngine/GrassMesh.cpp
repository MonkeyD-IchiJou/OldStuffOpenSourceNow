#include "GrassMesh.h"
#include "Vertex.h"
#include "MyMath.h"
using namespace Math;

namespace pp
{
	GrassMesh::GrassMesh(void)
	{
	}
	GrassMesh::~GrassMesh(void)
	{
		Clear();
	}
	bool GrassMesh::LoadMesh(void)
	{
		VertexGrass v;
		std::vector<VertexGrass> vertex_buffer_data;

		const float length = 2.5f;

		InitRNG();
		for (float x = 0; x < length; x += 0.06f)
		{
			for (float z = 0; z < length; z += 0.06f)
			{
				v.pos.Set(x - length/2.f, 0, z - length / 2.f);
				v.normal.Set(0, 1.f, 0);
				v.random.Set(RandFloatMinMax(0.5f, 1.5f), RandFloatMinMax(0.5f, 1.5f), RandFloatMinMax(0.5f, 1.5f));
				vertex_buffer_data.push_back(v);
			}
		}

		// Create the VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// Create the buffers for the vertices attributes
		glGenBuffers(1, &m_Buffers[0]);

		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(VertexGrass), &vertex_buffer_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexGrass), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexGrass), (void*)sizeof(vec3f));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexGrass), (void*)(sizeof(vec3f) + sizeof(vec3f)));

		IndexSize = vertex_buffer_data.size();

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);

		return true;
	}

	void GrassMesh::Render(void)
	{
		glBindVertexArray(m_VAO);

		glDrawArrays(GL_POINTS, 0, IndexSize);

		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}

	void GrassMesh::RenderWithoutBind(void)
	{
		glDrawArrays(GL_POINTS, 0, IndexSize);
	}
}