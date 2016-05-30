#include "TextMesh.h"
#include "utils.h"

#define FNT_POS_VB 0
#define FNT_TEXCOORD_VB 1

namespace pp
{
	TextMesh::TextMesh(void)
	{
	}


	TextMesh::~TextMesh(void)
	{
		Clear();
		clearVertices();
	}

	unsigned int TextMesh::getVertexCount(void) const
	{
		// do something dude
		return vertexPosition.size();
	}

	unsigned int TextMesh::getVaoID(void) const
	{
		return m_VAO;
	}

	void TextMesh::Render(void)
	{
		// render text
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		glBindVertexArray(0);
	}

	void TextMesh::RenderWithoutBind(void)
	{
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
	}

	void TextMesh::bindVertexAttribute(const GLenum & usage)
	{
		// make sure everything is empty
		Clear();

		// Create the VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);  // and then bind it

		// Create the buffers for the vertices attributes
		glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);


		// Generate and populate the buffers with vertex attributes and the indices
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[FNT_POS_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition[0]) * vertexPosition.size(), &vertexPosition[0], usage);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// for the texture coordinate
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[FNT_TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords[0]) * textureCoords.size(), &textureCoords[0], usage);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);
	}

	void TextMesh::updateVertexAttribute(void)
	{
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[FNT_POS_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition[0]) * vertexPosition.size(), &vertexPosition[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[FNT_TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords[0]) * textureCoords.size(), &textureCoords[0], GL_DYNAMIC_DRAW);

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);
	}

	void TextMesh::clearVertices(void)
	{
		vertexPosition.clear();
		textureCoords.clear();
	}
}