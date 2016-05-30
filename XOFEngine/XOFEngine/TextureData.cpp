#include "TextureData.h"

namespace pp
{
	TextureData::TextureData(void)
	{
		m_textureData = 0;
	}
	TextureData::TextureData(const unsigned int& l_data, const unsigned int&  l_width, const unsigned int&  l_height, GLubyte *	l_buffer, const unsigned int&  bytesPerPixel)
	{
		this->m_textureData = l_data;
		this->width = l_width;
		this->height = l_height;
		this->buffer = l_buffer;
		this->bytesPerPixel = bytesPerPixel;
	}
	TextureData::~TextureData(void)
	{
	}
	unsigned int TextureData::getTextureData(void) const
	{
		return this->m_textureData;
	}
	void TextureData::setTextureData(const unsigned int& l_data)
	{
		this->m_textureData = l_data;
	}
	unsigned int TextureData::getHeight(void) const
	{
		return this->height;
	}
	unsigned int TextureData::getWidth(void) const
	{
		return this->width;
	}
	GLubyte * TextureData::getBuffer(void) const
	{
		return this->buffer;
	}
	unsigned int TextureData::getBytesPerPixel(void) const
	{
		return this->bytesPerPixel;
	}
	void TextureData::cleanUpBuffer(void)
	{
		delete[]buffer;
	}
}
