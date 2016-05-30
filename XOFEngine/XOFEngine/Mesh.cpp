#include "Mesh.h"
using std::vector;

namespace pp
{

	Mesh::Mesh(void) : m_VAO(0), IndexSize(0)
	{
		ZERO_MEM(m_Buffers);
	}

	Mesh::~Mesh(void)
	{
	}
	bool Mesh::LoadMesh(const std::string & filename)
	{
		return false;
	}
	bool Mesh::LoadMesh()
	{
		return false;
	}

	void Mesh::bindVertexArray(void) const
	{
		glBindVertexArray(m_VAO);
	}

	void Mesh::Clear(void)
	{
		if (m_Buffers[0] != 0)
		{
			glDeleteBuffers(sizeof(m_Buffers) / sizeof(m_Buffers[0]), m_Buffers);
		}

		if (m_VAO != 0)
		{
			glDeleteVertexArrays(1, &m_VAO);
			m_VAO = 0;
		}
	}

	GLuint Mesh::getIndexSize(void) const
	{
		return IndexSize;
	}
}