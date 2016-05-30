#include "BasicMesh.h"
#include <assert.h>

using std::vector;

namespace pp
{
	BasicMesh::BasicMesh(void)
	{
	}

	BasicMesh::~BasicMesh(void)
	{
		Clear();
	}

	bool BasicMesh::LoadMesh(const std::string & filename)
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

	void BasicMesh::Render(void)
	{
		glBindVertexArray(m_VAO);

		for (unsigned int i = 0; i < m_Entries.size(); i++)
		{

			glDrawElementsBaseVertex(GL_TRIANGLES,
				m_Entries[i].NumIndices,
				GL_UNSIGNED_INT,
				(void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex),
				m_Entries[i].BaseVertex);
		}

		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}

	void BasicMesh::RenderWithoutBind(void)
	{
		for (unsigned int i = 0; i < m_Entries.size(); i++)
		{

			glDrawElementsBaseVertex(GL_TRIANGLES,
				m_Entries[i].NumIndices,
				GL_UNSIGNED_INT,
				(void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex),
				m_Entries[i].BaseVertex);
		}
	}

	bool BasicMesh::InitFromScene(const aiScene * pScene)
	{
		m_Entries.resize(pScene->mNumMeshes);

		vector<Vertex> vertex_buffer_data;
		vector<GLuint> index_buffer_data;

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
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3f));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3f) + sizeof(vec3f)));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3f) + sizeof(vec3f) + sizeof(TexCoord)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

		return true;
	}

	void BasicMesh::InitMesh(const aiMesh * paiMesh, std::vector<Vertex>& vertex_buffer_data, std::vector<unsigned int>& index_buffer_data)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		Vertex vertex;
		// Populate the vertex attribute vectors
		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
			const aiVector3D* pTangent = &(paiMesh->mTangents[i]);
			const aiVector3D* pBiTangent = &(paiMesh->mBitangents[i]);

			vertex.pos = vec3f(pPos->x, pPos->y, pPos->z);
			allTris.push_back(vertex.pos);
			vertex.normal = vec3f(pNormal->x, pNormal->y, pNormal->z);
			vertex.texCoord = TexCoord(pTexCoord->x, pTexCoord->y);

			if (paiMesh->HasTangentsAndBitangents())
			{
				vertex.tangent = vec3f(pTangent->x, pTangent->y, pTangent->z);
			}


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