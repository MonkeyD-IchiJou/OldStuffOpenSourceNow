#include "Word.h"
#include "Character.h"

namespace pp
{
	Word::Word(const float& fontSize)
	{
		this->fontSize = fontSize;
		this->width = 0.f;
	}

	Word::~Word(void)
	{
		// no need to delete characters .. because it will be deleted in MetaFile
		characters.clear();
	}

	void Word::addCharacter(Character * character)
	{
		characters.push_back(character);
		width += character->getxAdvance() * fontSize; // important is because .. when the next char come in .. know where to position it
	}

	float Word::getWordWidth(void) const
	{
		return width;
	}
}

