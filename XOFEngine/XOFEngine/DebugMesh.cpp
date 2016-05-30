#include "DebugMesh.h"
#include "MyMath.h"
#include "vec4.h"

using namespace Math;

namespace pp
{
	DebugMesh::DebugMesh(void) : instanceBuffer(0)
	{
	}
	DebugMesh::~DebugMesh(void)
	{
		if (instanceBuffer != 0)
		{
			glDeleteBuffers(1, &instanceBuffer);
		}

		Clear();
	}
	bool DebugMesh::LoadMesh(const std::string &filename)
	{
		// Release the previously loaded mesh (if it exists)
		Clear();

		// Create the VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// Create the buffers for the vertices attributes
		glGenBuffers(2, m_Buffers);

		bool Ret = false;
		Assimp::Importer Importer;

		const aiScene* pScene = Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_FindDegenerates | aiProcess_CalcTangentSpace);

		if (pScene)
		{
			Ret = InitFromScene(pScene);
		}

		else
		{
			printf("Error parsing '%s': '%s'\n", filename.c_str(), Importer.GetErrorString());
		}

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);

		//// can delete the damn buffers alr
		if (m_Buffers[0] != 0)
		{
			glDeleteBuffers(sizeof(m_Buffers) / sizeof(m_Buffers[0]), m_Buffers);
		}

		return false;
	}

	void DebugMesh::Render(void)
	{
		glBindVertexArray(m_VAO);

		glDrawArrays(GL_POINTS, 0, IndexSize);

		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}

	void DebugMesh::RenderWithoutBind(void)
	{
		glDrawArrays(GL_POINTS, 0, IndexSize);
	}

	void DebugMesh::RenderInstanced( std::vector<mat4f>& modelMatrices)
	{
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(mat4f), &modelMatrices[0], GL_DYNAMIC_DRAW);

		glDrawElementsInstanced(GL_LINE_STRIP, IndexSize, GL_UNSIGNED_INT, 0, modelMatrices.size());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);

	}

	void DebugMesh::RenderInstancedTriangle(const std::vector<mat4f>& modelMatrices)
	{
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(mat4f), &modelMatrices[0], GL_DYNAMIC_DRAW);

		glDrawElementsInstanced(GL_TRIANGLES, IndexSize, GL_UNSIGNED_INT, 0, modelMatrices.size());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}

	bool DebugMesh::InitFromScene(const aiScene * pScene)
	{
		m_Entries.resize(pScene->mNumMeshes);

		std::vector<vec3f> vertex_buffer_data;
		std::vector<GLuint> index_buffer_data;

		unsigned int NumVertices = 0;
		unsigned int NumIndices = 0;

		// Count the number of vertices and indices
		for (unsigned int i = 0; i < m_Entries.size(); i++)
		{
			m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
			m_Entries[i].BaseVertex = NumVertices;
			m_Entries[i].BaseIndex = NumIndices;

			NumVertices += pScene->mMeshes[i]->mNumVertices;
			NumIndices += m_Entries[i].NumIndices;
		}

		vertex_buffer_data.reserve(NumVertices);
		index_buffer_data.reserve(NumVertices);

		// Initialize the meshes in the scene one by one
		for (unsigned int i = 0; i < m_Entries.size(); i++)
		{
			const aiMesh* paiMesh = pScene->mMeshes[i];
			InitMesh(paiMesh, vertex_buffer_data, index_buffer_data);
		}

		// Set the current active buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
		// Transfer vertices to OpenGL
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(vec3f), &vertex_buffer_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3f), (void*)0);

		// unbind the current vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// instancing
		glGenBuffers(1, &instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);

		// vertex attributes
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(mat4f), (GLvoid*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4f), (GLvoid*)(sizeof(vec4f)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4f), (GLvoid*)(2 * sizeof(vec4f)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4f), (GLvoid*)(3 * sizeof(vec4f)));

		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);

		// unbind the current vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

		return true;
	}

	void DebugMesh::InitMesh(const aiMesh * paiMesh, std::vector<vec3f>& vertex_buffer_data, std::vector<unsigned int>& index_buffer_data)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		vec3f vertex;

		// Populate the vertex attribute vectors
		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);

			vertex = vec3f(pPos->x, pPos->y, pPos->z);

			allTris.push_back(vertex);
			vertex_buffer_data.push_back(vertex);
		}

		// Populate the index buffer
		for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
		{
			const aiFace& Face = paiMesh->mFaces[i];
			//assert(Face.mNumIndices == 3);
			index_buffer_data.push_back(Face.mIndices[0]);
			index_buffer_data.push_back(Face.mIndices[1]);
			index_buffer_data.push_back(Face.mIndices[2]);
		}

		IndexSize = index_buffer_data.size();
	}
}