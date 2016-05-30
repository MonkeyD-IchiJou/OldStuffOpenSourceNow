#ifndef METAFILE_H
#define METAFILE_H

#include "vec4.h"
#include <string>
#include <map>
#include <fstream>

using std::map;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

using namespace Math;

namespace pp
{
	class Character;

	class MetaFile
	{
	public:
		MetaFile(string fontFileName);
		~MetaFile(void);

		// getter
		float getSpaceWidth(void) const;

		// storage for all the characters .. int == acsii
		map<int, Character*> metaData;

		static const int DESIRED_PADDING = 8;
		static const int SPACE_ASCII = 32;
		static float LINE_HEIGHT;

	private:
		float aspectRatio;
		float verticalPerPixelSize;
		float horizontalPerPixelSize;
		float spaceWidth;
		vec4f padding;
		int paddingWidth;
		int paddingHeight;

		ifstream reader;

	private:
		// Opens the font file, ready for reading.
		void openFile(string fontFileName);

		//Loads the data about how much padding is used around each character in the texture atlas.
		void loadPaddingData(void);

		// Loads information about the line height for this font in pixels, and uses
		// this as a way to find the conversion rate between pixels in the texture
		// atlas and screen - space.
		void loadLineSizes(void);

		// Loads in data about each character and stores the data in the class
		void loadCharacterData(int imageWidth);

		// Loads all the data about one character in the texture atlas and converts
		// it all from 'pixels' to 'screen-space' before storing.The effects of
		// padding are also removed from the data.
		// will retrun a new dynamic character
		Character* loadCharacter(int imageSize);

		// Closes the font file after finishing reading.
		void close(void);

	};
}

#endif


