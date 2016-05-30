#include "AxisLineMesh.h"
#include "Vertex.h"
using namespace Math;

namespace pp
{
	AxisLineMesh::AxisLineMesh(void)
	{
	}
	AxisLineMesh::~AxisLineMesh(void)
	{
		Clear();
	}
	bool AxisLineMesh::LoadMesh()
	{
		Vertex v;
		std::vector<Vertex> vertex_buffer_data;
		v.pos.Set(-1000.f, 0, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(1000.f, 0, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, -1000.f, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, 1000.f, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, -1000.f);
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 1000.f);
		vertex_buffer_data.push_back(v);

		std::vector<GLuint> index_buffer_data;
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(1);
		index_buffer_data.push_back(2);
		index_buffer_data.push_back(3);
		index_buffer_data.push_back(4);
		index_buffer_data.push_back(5);


		// Create the VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// Create the buffers for the vertices attributes
		glGenBuffers(2, m_Buffers);

		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

		IndexSize = index_buffer_data.size();

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);

		return true;
	}

	void AxisLineMesh::Render(void)
	{
		glBindVertexArray(m_VAO);

		glDrawElements(GL_LINES, IndexSize, GL_UNSIGNED_INT, 0);

		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}

	void AxisLineMesh::RenderWithoutBind(void)
	{
		glDrawElements(GL_LINES, IndexSize, GL_UNSIGNED_INT, 0);
	}
}