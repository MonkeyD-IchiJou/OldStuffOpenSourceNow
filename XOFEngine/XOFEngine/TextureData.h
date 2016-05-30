
#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#include "GLH.h"

namespace pp
{
	class TextureData
	{
	public:
		TextureData(void);
		TextureData(const unsigned int& l_data, const unsigned int&  l_width, const unsigned int&  l_height, GLubyte *	l_buffer, const unsigned int&  bytesPerPixel);
		~TextureData(void);

		unsigned int getTextureData(void) const;
		void setTextureData(const unsigned int& l_data);

		unsigned int getHeight(void) const;
		unsigned int getWidth(void) const;
		GLubyte* getBuffer(void) const;
		unsigned int getBytesPerPixel(void) const;

		void cleanUpBuffer(void);

	private:
		unsigned int m_textureData;

		unsigned int width, height, bytesPerPixel;
		GLubyte * buffer;
	};
}
#endif
