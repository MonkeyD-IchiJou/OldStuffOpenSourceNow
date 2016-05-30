#include "FontType.h"
#include "TextMeshCreator.h"
#include "GUIText.h"

namespace pp
{
	FontType::FontType(unsigned int texID, string fileName)
	{
		this->TextureID = texID;
		this->loader = new TextMeshCreator(fileName);
	}

	FontType::~FontType(void)
	{
		delete loader;
	}

	unsigned int FontType::getTexID(void)
	{
		return this->TextureID;
	}

	void FontType::bindTex(const GLenum & active)
	{
		glActiveTexture(active);
		glBindTexture(GL_TEXTURE_2D, TextureID);
	}

	TextMesh * FontType::loadText(GUIText * text)
	{
		return loader->createTextMesh(text);
	}

	void FontType::updateText(GUIText * text, TextMesh * data)
	{
		loader->updateTextMesh(text, data);
	}
}
