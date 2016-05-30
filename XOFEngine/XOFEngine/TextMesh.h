#ifndef TEXTMESHDATA_H
#define TEXTMESHDATA_H

#include "Vertex.h"
#include "Mesh.h"

using namespace Math;
using std::vector;

namespace pp
{
	class TextMesh : Mesh
	{
	public:
		TextMesh(void);
		~TextMesh(void);

		unsigned int getVertexCount(void) const;
		unsigned int getVaoID(void) const;

		void Render(void) override;
		void RenderWithoutBind(void) override;

		vector<vec3f> vertexPosition;
		vector<TexCoord> textureCoords;

		void bindVertexAttribute(const GLenum& usage);
		void updateVertexAttribute(void);

		void clearVertices(void);
	};
}

#endif
