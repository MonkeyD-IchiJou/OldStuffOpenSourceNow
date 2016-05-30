#ifndef TEXTURE_LIBRARY_H
#define TEXTURE_LIBRARY_H

#include <map>
#include <string>



using std::string;
using std::map;

namespace pp
{
	class Texture;

	class TextureLibrary
	{
	public:
		map<string, Texture*> diffMap;
		map<string, Texture*> normMap;
		map<string, Texture*> Fonts;

		void init(void);
		void cleanUP(void);

		// Singleton class implementation
		static inline TextureLibrary* getInstance(void)
		{
			if (s_instance == NULL)
			{
				s_instance = new TextureLibrary();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		// singleton properties
		static TextureLibrary* s_instance;

		TextureLibrary(void);
		~TextureLibrary(void);

		void initAllDiffuseMapping(void);
		void initAllNormalMapping(void);
		void initAllFonts(void);
	};
}


#endif

