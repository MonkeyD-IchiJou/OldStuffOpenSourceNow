#include "LineMesh.h"
#include "Vertex.h"
using namespace Math;

namespace pp
{
	LineMesh::LineMesh(void)
	{
		pos.SetZero();
		tar.Set(0, 0, 0);
	}
	LineMesh::~LineMesh(void)
	{
		Clear();
	}
	bool LineMesh::LoadMesh(void)
	{
		std::vector<vec3f> vertex_buffer_data;
		vertex_buffer_data.push_back(pos);
		vertex_buffer_data.push_back(tar);

		// Create the VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// Create the buffers for the vertices attributes
		glGenBuffers(1, &m_Buffers[0]);

		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(vec3f), &vertex_buffer_data[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);

		return true;
	}

	void LineMesh::Render(void)
	{
		glBindVertexArray(m_VAO);

		glDrawArrays(GL_LINES, 0, 2);

		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}

	void LineMesh::RenderWithoutBind(void)
	{
		// nothing
	}

	void LineMesh::updatePosAndTar(const vec3f & pos, const vec3f & tar)
	{
		std::vector<vec3f> vertex_buffer_data;
		vertex_buffer_data.push_back(pos);
		vertex_buffer_data.push_back(tar);

		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(vec3f), &vertex_buffer_data[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}