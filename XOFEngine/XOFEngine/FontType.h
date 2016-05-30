#ifndef FONTTYPE_H
#define FONTTYPE_H

#include "GLH.h"
#include <string>
using std::string;

namespace pp
{
	// Represents a font. It holds the font's texture atlas as well as having the
	// ability to create the quad vertices for any text using this font.

	class TextMeshCreator;
	class TextMesh;
	class GUIText;

	class FontType
	{
	public:
		// Creates a new font and loads up the data about each character from the
		// font file.
		FontType(unsigned int texID, string fileName);

		// destructor biatch
		~FontType(void);

		unsigned int getTexID(void);
		void bindTex(const GLenum& active);
		TextMesh* loadText(GUIText *text);
		void updateText(GUIText* text, TextMesh* data);

	private:
		TextMeshCreator* loader;
		unsigned int TextureID;
	};
}

#endif

