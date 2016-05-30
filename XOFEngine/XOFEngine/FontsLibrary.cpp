#include "FontsLibrary.h"
#include "TextureLibrary.h"
#include "Texture.h"

#include "FontType.h"
namespace pp
{
	FontsLibrary * FontsLibrary::s_instance = nullptr;

	void FontsLibrary::initAllFonts(void)
	{
		// prevent memory leak
		cleanUp();

		TextureLibrary* tl = TextureLibrary::getInstance();

		FontTypes["FORCESQUARE"] = new FontType(tl->Fonts["FORCESQUARE"]->getTextureID(), "Content//meshes//Fonts//forcesquare.FNT");

		FontTypes["POLYGONFONT"] = new FontType(tl->Fonts["POLYGONFONT"]->getTextureID(), "Content//meshes//Fonts//polygonfont.FNT");

		FontTypes["PRISMFONT"] = new FontType(tl->Fonts["PRISMFONT"]->getTextureID(), "Content//meshes//Fonts//prismfont.FNT");
		
	}

	void FontsLibrary::cleanUp(void)
	{
		for (auto &x : FontTypes)
		{
			delete x.second;
		}

		FontTypes.clear();
	}

	FontsLibrary::FontsLibrary(void)
	{
	}

	FontsLibrary::~FontsLibrary(void)
	{
		cleanUp();
	}

}