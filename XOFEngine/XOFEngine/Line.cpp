#include "Line.h"
#include "Word.h"

namespace pp
{

	Line::Line(const float& spaceWidth, const float& fontSize, const float& maxLength) : currentLineLength(0.f)
	{
		this->spaceSize = spaceWidth * fontSize;
		this->maxLength = maxLength;
	}

	bool Line::attemptToAddWord(Word* word)
	{
		float additionalLength = word->getWordWidth();

		// if words is not empty
		if (!words.empty())
		{
			additionalLength += spaceSize;
		}

		if ((currentLineLength + additionalLength) <= maxLength)
		{
			words.push_back(word);
			currentLineLength += additionalLength;

			return true;
		}
		else
		{
			return false;
		}
	}

	float Line::getMaxLength(void) const
	{
		return maxLength;
	}

	float Line::getLineLength(void) const
	{ 
		return currentLineLength;
	}

	Line::~Line(void)
	{
		// maybe delete all the words here
		for (auto &W : words)
		{
			delete W;
		}

		words.clear();
	}
}