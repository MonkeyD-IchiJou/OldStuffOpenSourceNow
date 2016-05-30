#include "MetaFile.h"
#include "GLFW_Window.h"
#include "Character.h"

namespace pp
{
	float MetaFile::LINE_HEIGHT = 0.03f;

	MetaFile::MetaFile(string fontFileName)
	{
		if (GLFW_Window::getInstance()->getFullScreenInfo())
		{
			this->aspectRatio = static_cast<float>(GLFW_Window::getInstance()->getMonitorWidth()) / static_cast<float>(GLFW_Window::getInstance()->getMonitorHeight());
		}

		else
		{
			this->aspectRatio = static_cast<float>(GLFW_Window::getInstance()->getWindowWidth()) / static_cast<float>(GLFW_Window::getInstance()->getWindowHeight());
		}

		openFile(fontFileName);
		loadPaddingData();
		loadLineSizes();
		int imageWidth = 512; // always 512
		loadCharacterData(imageWidth);

		close();
	}

	MetaFile::~MetaFile(void)
	{
		for (auto &x : metaData)
		{
			delete x.second;
		}
		metaData.clear();
	}

	float MetaFile::getSpaceWidth(void) const
	{
		return this->spaceWidth;
	}

	void MetaFile::openFile(string fontFileName)
	{
		reader.open(fontFileName, std::ios::in);

		// if the file cannot open
		if (!reader.is_open())
		{
			printf("cannot open font file");
			throw 0;
		}
	}

	void MetaFile::loadPaddingData(void)
	{
		string name;
		string variable;

		std::getline(reader, name, ' ');

		if (name == "info")
		{
			while (1)
			{
				std::getline(reader, name, '=');

				if (name == "padding")
				{
					std::getline(reader, variable, ',');
					padding.x = stof(variable);

					std::getline(reader, variable, ',');
					padding.y = stof(variable);

					std::getline(reader, variable, ',');
					padding.z = stof(variable);

					std::getline(reader, variable, ' ');
					padding.w = stof(variable);

					break;

				}

				else
				{
					std::getline(reader, variable, ' ');
				}
			}
		}

		this->paddingHeight = static_cast<int>(padding.y + padding.w);
		this->paddingWidth = static_cast<int>(padding.x + padding.z);
	}

	void MetaFile::loadLineSizes(void)
	{
		string name;
		string variable;
		int lineHeight = 0;

		std::getline(reader, name);
		std::getline(reader, name, ' ');

		if (name == "common")
		{
			while (1)
			{
				std::getline(reader, name, '=');

				if (name == "lineHeight")
				{
					std::getline(reader, variable, ' ');
					lineHeight = stoi(variable);

					break;
				}

				else
				{
					std::getline(reader, variable, ' ');
				}
			}
		}

		int lineHeightPixels = lineHeight - paddingHeight;
		verticalPerPixelSize = LINE_HEIGHT / static_cast<float>(lineHeightPixels);
		horizontalPerPixelSize = verticalPerPixelSize / aspectRatio;
	}

	void MetaFile::loadCharacterData(int imageWidth)
	{
		string name;

		std::getline(reader, name);
		std::getline(reader, name);
		std::getline(reader, name);

		while (!reader.eof())
		{
			Character *c = loadCharacter(imageWidth);

			if (c != nullptr)
			{
				metaData[c->getId()] = c;
			}
		}
	}

	Character * MetaFile::loadCharacter(int imageSize)
	{
		int id_t = 0;
		int x_t = 0, y_t = 0, width_t = 0, height_t = 0, xoffset_t = 0, yoffset_t = 0, xadvance_t = 0;

		string variable;
		const static int len = 32;
		char check[len];
		ZERO_MEM(check);

		// id
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		if (variable.empty())
		{
			return nullptr;
		}
		id_t = std::stoi(variable);

		// x
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		x_t = std::stoi(variable);

		// y
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		y_t = std::stoi(variable);

		// width 
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		width_t = std::stoi(variable);

		// height 
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		height_t = std::stoi(variable);

		// xoffset
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		xoffset_t = std::stoi(variable);

		// yoffset
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		yoffset_t = std::stoi(variable);

		// xadvance
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');
		xadvance_t = std::stoi(variable);

		// extra
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');

		// extra
		reader.getline(check, len, '=');
		std::getline(reader, variable, ' ');

		if (id_t == SPACE_ASCII)
		{
			this->spaceWidth = (xadvance_t - paddingWidth) * horizontalPerPixelSize;
			return nullptr;
		}

		float xTex = ((float)x_t + ((int)padding.y - DESIRED_PADDING)) / imageSize;
		float yTex = ((float)y_t + ((int)padding.x - DESIRED_PADDING)) / imageSize;
		int width = width_t - (paddingWidth - (2 * DESIRED_PADDING));
		int height = height_t - ((paddingHeight)-(2 * DESIRED_PADDING));
		float quadWidth = width * horizontalPerPixelSize;
		float quadHeight = height * verticalPerPixelSize;
		float xTexSize = (float)(width) / imageSize;
		float yTexSize = (float)(height) / imageSize;
		float xOff = (xoffset_t + (int)padding.y - DESIRED_PADDING) * horizontalPerPixelSize;
		float yOff = (yoffset_t + ((int)padding.x - DESIRED_PADDING)) * verticalPerPixelSize;
		float xAdvance = (xadvance_t - paddingWidth) * horizontalPerPixelSize;
		return new Character(id_t, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
	}

	void MetaFile::close(void)
	{
		reader.close();
	}
}