#include "TextMeshCreator.h"
#include "MetaFile.h"
#include "Line.h"
#include "GUIText.h"
#include "Word.h"
#include "TextMesh.h"
#include "Character.h"

namespace pp
{
	TextMeshCreator::TextMeshCreator(const string& filename)
	{
		// load the FNT file .. and extract the char info to the map<int, character*> 
		metaData = new MetaFile(filename);
	}

	TextMeshCreator::~TextMeshCreator(void)
	{
		delete metaData;
	}

	TextMesh * TextMeshCreator::createTextMesh(GUIText * text)
	{
		TextMesh* data = new TextMesh(); // this will be deleted in GUItext

		vector<Line*> lines = createStructure(text); // check got how many lines first
		createQuadVertices(text, lines, data);

		text->setTextLength(lines[0]->getLineLength());

		// rmb to delete it .. dun need this anymore
		for (auto l : lines)
		{
			delete l;
		}

		return data;
	}

	void TextMeshCreator::updateTextMesh(GUIText * text, TextMesh * data)
	{
		vector<Line*> lines = createStructure(text); // check got how many lines first
		createQuadVertices(text, lines, data);

		text->setTextLength(lines[0]->getLineLength());

		// rmb to delete it .. dun need this anymore
		for (auto l : lines)
		{
			delete l;
		}
	}

	vector<Line*> TextMeshCreator::createStructure(GUIText * text)
	{
		string chars = text->getTextString();

		if (chars.empty())
		{
			printf( "empty text" );
			throw 0;
		}
		vector<Line*> lines;

		Line * currentLine = new Line(metaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize());
		Word* currentWord = new Word(text->getFontSize());

		// loop through the whole string and store word and lines
		for (auto &c : chars)
		{
			int ascii = (int)c;

			// if reach space char .. it is time to store it into the line
			if (ascii == MetaFile::SPACE_ASCII)
			{
				bool added = currentLine->attemptToAddWord(currentWord);

				if (!added)
				{
					lines.push_back(currentLine);
					currentLine = new Line(metaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize());
					currentLine->attemptToAddWord(currentWord);
				}

				// if reach here
				// currentword confirm added into currentLine
				currentWord = new Word(text->getFontSize());
				continue;
			}

			// else add the character into the word first
			Character* character = metaData->metaData[ascii];
			currentWord->addCharacter(character);
		}

		completeStructure(lines, currentLine, currentWord, text);

		return lines;
	}

	void TextMeshCreator::completeStructure(vector<Line*>& lines, Line * currentLine, Word * currentWord, GUIText * text)
	{
		bool added = currentLine->attemptToAddWord(currentWord);

		if (!added)
		{
			lines.push_back(currentLine);
			currentLine = new Line(metaData->getSpaceWidth(), text->getFontSize(), text->getMaxLineSize());
			currentLine->attemptToAddWord(currentWord);
		}

		lines.push_back(currentLine);
	}

	void TextMeshCreator::createQuadVertices(GUIText * text, vector<Line*>& lines, TextMesh* textMeshData)
	{
		text->setNumberofLines(lines.size());

		float curserX = 0.f;
		float curserY = 0.f;

		for (auto &line : lines)
		{
			if (text->isCentered())
			{
				curserX = (line->getMaxLength() - line->getLineLength()) / 2;
			}

			for (auto &word : line->words)
			{
				for (auto letter : word->characters)
				{
					addVerticesForCharacter(curserX, curserY, letter, text->getFontSize(), textMeshData->vertexPosition);
					addTexCoords(textMeshData->textureCoords, letter->getxTextureCoord(), letter->getyTextureCoord(),
						letter->getXMaxTextureCoord(), letter->getYMaxTextureCoord());

					curserX += letter->getxAdvance() * text->getFontSize();
				}
				curserX += metaData->getSpaceWidth() * text->getFontSize();
			}

			curserX = 0;
			curserY += MetaFile::LINE_HEIGHT * text->getFontSize();
		}
	}

	void TextMeshCreator::addVerticesForCharacter(const float& curserX, const float& curserY, Character* character, const float& fontSize,
		vector<vec3f>& vertices)
	{
		float x = curserX + (character->getxOffset() * fontSize);
		float y = curserY + (character->getyOffset() * fontSize);
		float maxX = x + (character->getSizeX() * fontSize);
		float maxY = y + (character->getSizeY() * fontSize);
		float properX = (2 * x) - 1;
		float properY = (-2 * y) + 1;
		float properMaxX = (2 * maxX) - 1;
		float properMaxY = (-2 * maxY) + 1;
		addVertices(vertices, properX, properY, properMaxX, properMaxY);
	}

	void TextMeshCreator::addVertices(vector<vec3f>& vertices, const float & x, const float & y, const float & maxX, const float & maxY)
	{
		vertices.push_back(vec3f(x, y, 0.f));

		vertices.push_back(vec3f(x, maxY, 0.f));

		vertices.push_back(vec3f(maxX, maxY, 0.f));

		vertices.push_back(vec3f(maxX, maxY, 0.f));

		vertices.push_back(vec3f(maxX, y, 0.f));

		vertices.push_back(vec3f(x, y, 0.f));
	}

	void TextMeshCreator::addTexCoords(vector<TexCoord>& texCoords, const float & x, const float & y, const float & maxX, const float & maxY)
	{
		texCoords.push_back(TexCoord(x, 1.f - y));

		texCoords.push_back(TexCoord(x, 1.f - maxY));

		texCoords.push_back(TexCoord(maxX, 1.f - maxY));

		texCoords.push_back(TexCoord(maxX, 1.f - maxY));

		texCoords.push_back(TexCoord(maxX, 1.f - y));

		texCoords.push_back(TexCoord(x, 1.f - y));
	}


}