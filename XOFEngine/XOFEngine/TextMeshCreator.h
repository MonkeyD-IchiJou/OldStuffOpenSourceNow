#ifndef TEXTMESHCREATOR_H
#define TEXTMESHCREATOR_h

#include <string>
#include <vector>
#include "Vertex.h"

using std::vector;
using std::string;

namespace pp
{
	class MetaFile;
	class TextMesh;
	class GUIText;
	class Line;
	class Word;
	class Character;

	class TextMeshCreator
	{
	public:
		TextMeshCreator(const string& filename);
		~TextMeshCreator(void);

		TextMesh* createTextMesh( GUIText* text );
		void updateTextMesh(GUIText* text, TextMesh* data);

	protected:
		vector<Line*> createStructure( GUIText* text);
		void completeStructure(vector<Line*> &lines, Line* currentLine, Word* currentWord, GUIText* text);
		
		void createQuadVertices(GUIText* text, vector<Line*> &lines, TextMesh* textMeshData);
		void addVerticesForCharacter(const float& curserX, const float& curserY, Character* character, const float& fontSize,
			vector<vec3f>& vertices);


		static void addVertices(vector<vec3f>& vertices, const float & x, const float & y, const float & maxX, const float & maxY);
		static void addTexCoords(vector<TexCoord>& texCoords, const float& x, const float & y, const float & maxX, const float & maxY);

	private:
		MetaFile* metaData;
	};
}

#endif
