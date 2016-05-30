#ifndef LINE_H
#define LINE_H

#include <vector>
using std::vector;

namespace pp
{
	class Word;

	class Line
	{
	public:
		// Creates an empty line.
		Line(const float& spaceWidth, const float& fontSize, const float& maxLength);

		// attemp to add a word to the line. if the line can fit the word in 
		// without reaching the maximum line length then theword is added and the line length increased.
		bool attemptToAddWord(Word* word);

		// return the max length of the line
		float getMaxLength(void) const;

		// return teh current screen-space length of the line
		float getLineLength(void) const;

		// all the words tht are on the line (this)
		// each word got their own set of characters
		vector<Word*> words;

		// destructor
		~Line();

	private:
		float maxLength;
		float spaceSize;
		float currentLineLength;
	};
}

#endif

