#include "TextureLibrary.h"
#include "Texture.h"

namespace pp
{
	TextureLibrary* TextureLibrary::s_instance = nullptr;

	void TextureLibrary::init(void)
	{
		// prevent memory leak
		cleanUP();

		initAllDiffuseMapping();
		initAllNormalMapping();
		initAllFonts();
	}

	void TextureLibrary::initAllDiffuseMapping(void)
	{
		diffMap["LENSCOLOR"] = new Texture(GL_TEXTURE_2D);
		diffMap["LENSCOLOR"]->load("Content//meshes//LensFlare//lenscolor.tga", false);

		diffMap["LENSDIRT"] = new Texture(GL_TEXTURE_2D);
		diffMap["LENSDIRT"]->load("Content//meshes//LensFlare//lensdirt.tga", false);

		diffMap["LENSSTAR"] = new Texture(GL_TEXTURE_2D);
		diffMap["LENSSTAR"]->load("Content//meshes//LensFlare//lensstar.tga", false);

		diffMap["BLACK"] = new Texture(GL_TEXTURE_2D);
		diffMap["BLACK"]->load("Content//meshes//Texture//black.tga", true);

		diffMap["SKYBOX_1"] = new Texture(GL_TEXTURE_CUBE_MAP);
		diffMap["SKYBOX_1"]->loadCubeMapTex(
			"Content//meshes//SkyBox//spires_lf.tga", 
			"Content//meshes//SkyBox//spires_rt.tga", 
			"Content//meshes//SkyBox//spires_up.tga", 
			"Content//meshes//SkyBox//spires_dn.tga", 
			"Content//meshes//SkyBox//spires_bk.tga",
			"Content//meshes//SkyBox//spires_ft.tga");

		diffMap["SKYBOX_HILLS"] = new Texture(GL_TEXTURE_CUBE_MAP);
		diffMap["SKYBOX_HILLS"]->loadCubeMapTex(
			"Content//meshes//SkyBox//hills_lf.tga",
			"Content//meshes//SkyBox//hills_rt.tga",
			"Content//meshes//SkyBox//hills_up.tga",
			"Content//meshes//SkyBox//hills_dn.tga",
			"Content//meshes//SkyBox//hills_bk.tga",
			"Content//meshes//SkyBox//hills_ft.tga");

	}

	
	void TextureLibrary::initAllNormalMapping(void)
	{
	}

	void TextureLibrary::initAllFonts(void)
	{
		Fonts["FORCESQUARE"] = new Texture(GL_TEXTURE_2D);
		Fonts["FORCESQUARE"]->load("Content//meshes//Fonts//forcesquare.tga", false);

		Fonts["POLYGONFONT"] = new Texture(GL_TEXTURE_2D);
		Fonts["POLYGONFONT"]->load("Content//meshes//Fonts//polygonfont.tga", false);

		Fonts["PRISMFONT"] = new Texture(GL_TEXTURE_2D);
		Fonts["PRISMFONT"]->load("Content//meshes//Fonts//prismfont.tga", false);
	}

	void TextureLibrary::cleanUP(void)
	{
		if (diffMap.size() != 0)
		{
			for (map<string, Texture*>::iterator it = diffMap.begin(); it != diffMap.end(); ++it)
			{
				delete it->second;
			}
			diffMap.clear();
		}

		if (normMap.size() != 0)
		{
			for (map<string, Texture*>::iterator it = normMap.begin(); it != normMap.end(); ++it)
			{
				delete it->second;
			}
			normMap.clear();
		}
	}

	TextureLibrary::TextureLibrary(void)
	{
	}

	TextureLibrary::~TextureLibrary(void)
	{
		cleanUP();
	}
}
