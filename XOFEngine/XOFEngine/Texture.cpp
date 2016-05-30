#include "Texture.h"
#include "TextureData.h"
#include <fstream>

namespace pp
{
	Texture::Texture(const GLenum& TextureTarget) : m_textureTarget(TextureTarget), t_data(nullptr)
	{
	}


	Texture::~Texture(void)
	{
		glDeleteTextures(1, &m_textureID);
	}


	bool Texture::load(const std::string& FileName, bool gamma, GLint param_minF, GLint param_maxF, GLint param_S, GLint param_T)
	{
		decodeTextureFile(FileName);

		glGenTextures(1, &m_textureID);
		t_data->setTextureData(m_textureID);

		glBindTexture(GL_TEXTURE_2D, m_textureID);

		GLint interform = GL_RGB;
		GLint interform2 = GL_RGBA;

		if (gamma)
		{
			interform = GL_SRGB;
			interform2 = GL_SRGB_ALPHA;
		}

		if (t_data->getBytesPerPixel() == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, interform, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		}

		else //bytesPerPixel == 4
		{
			// try change the BGRA to RGBA     // t_data is the buffer that thin matrix is talking about
			glTexImage2D(GL_TEXTURE_2D, 0, interform2, t_data->getWidth(), t_data->getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, t_data->getBuffer());
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param_minF);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param_maxF);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

		float maxAnisotropy = 1.f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy / 2);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param_S);       // try change to GL_CLAMP or GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param_T);

		t_data->cleanUpBuffer();

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	bool Texture::loadCubeMapTex(const std::string& f1, const std::string& f2, const std::string& f3, const std::string& f4, const std::string& f5, const std::string& f6)
	{
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

		decodeTextureFile(f1);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_SRGB, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		t_data->cleanUpBuffer();
		delete t_data;

		decodeTextureFile(f2);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_SRGB, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		t_data->cleanUpBuffer();
		delete t_data;

		decodeTextureFile(f3);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_SRGB, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		t_data->cleanUpBuffer();
		delete t_data;

		decodeTextureFile(f4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_SRGB, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		t_data->cleanUpBuffer();
		delete t_data;

		decodeTextureFile(f5);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_SRGB, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		t_data->cleanUpBuffer();
		delete t_data;

		decodeTextureFile(f6);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_SRGB, t_data->getWidth(), t_data->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, t_data->getBuffer());
		t_data->cleanUpBuffer();
		// keep the last one

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		t_data->setTextureData(m_textureID);

		return true;
	}

	void Texture::Bind(const GLenum& textureUnit) const
	{
		glActiveTexture(textureUnit);
		glBindTexture(m_textureTarget, m_textureID);
	}

	GLuint Texture::getTextureID(void) const
	{
		return this->m_textureID;
	}

	void Texture::decodeTextureFile(const std::string& m_filename)
	{

		// use string is ok de
		std::ifstream fileStream(m_filename, std::ios::binary);
		if (!fileStream.is_open())
		{
			throw 0;
			return;
		}

		GLubyte		header[18];									// first 6 useful header bytes
		GLuint		bytesPerPixel;								    // number of bytes per pixel in TGA gile
		GLuint		imageSize;									    // for setting memory
		GLubyte *	data = nullptr;
		GLuint		texture = 0;
		unsigned	width, height;

		fileStream.read((char*)header, 18);
		width = header[12] + header[13] * 256;
		height = header[14] + header[15] * 256;

		if (width <= 0 ||								// is width <= 0
			height <= 0 ||								// is height <=0
			(header[16] != 24 && header[16] != 32))		// is TGA 24 or 32 Bit
		{
			fileStream.close();							// close file on failure
			throw 0;
			return;
		}

		bytesPerPixel = header[16] / 8;						//divide by 8 to get bytes per pixel
		imageSize = width * height * bytesPerPixel;	// calculate memory required for TGA t_data

		data = new GLubyte[imageSize];
		fileStream.seekg(18, std::ios::beg);
		fileStream.read((char *)data, imageSize);
		fileStream.close();

		t_data = new TextureData(texture, width, height, data, bytesPerPixel);
	}
}