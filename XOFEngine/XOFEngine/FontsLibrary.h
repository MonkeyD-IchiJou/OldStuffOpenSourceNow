#ifndef FONTSLIBRARY_H
#define FONTSLIBRARY_H

#include <map>
#include <string>

using std::string;
using std::map;

namespace pp
{
	class FontType;
	class FontsLibrary
	{
	public:
		
		void initAllFonts(void);
		void cleanUp(void);

		map<string, FontType*> FontTypes;

		// Singleton class implementation
		static inline FontsLibrary* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new FontsLibrary();
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
		static FontsLibrary* s_instance;

		FontsLibrary(void);
		~FontsLibrary(void);

	};
}

#endif

