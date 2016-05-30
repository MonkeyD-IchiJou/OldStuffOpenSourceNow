#ifndef WORD_H
#define WORD_h

#include <vector>
using std::vector;

namespace pp
{
	class Character;

	// During the loading of a text this represents one word in the text.

	class Word
	{
	public:
		// Create a new empty word.
		Word(const float& fontSize);

		// destructor
		~Word(void);

		// Adds a character to the end of the current word and increases the screen-space width of the word.
		void addCharacter(Character* character);

		// return teh width of the word in terms of screen size
		float getWordWidth(void) const;

		// in this one word .. we got this amount of characters
		vector<Character*>characters;

	private:
		float width;
		float fontSize;

	};
}

#endif

