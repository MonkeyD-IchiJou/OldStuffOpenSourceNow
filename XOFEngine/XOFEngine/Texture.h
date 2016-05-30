#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLH.h"
#include <string>


namespace pp
{
	class TextureData;

	class Texture
	{
	public:
		Texture(const GLenum& TextureTarget);
		~Texture(void);

		bool load(const std::string& FileName, bool gamma = true, GLint param_minF = GL_LINEAR_MIPMAP_NEAREST, GLint param_maxF = GL_LINEAR_MIPMAP_NEAREST, GLint param_S = GL_CLAMP_TO_EDGE, GLint param_T = GL_CLAMP_TO_EDGE);
		bool loadCubeMapTex(const std::string& f1, const std::string& f2, const std::string& f3, const std::string& f4, const std::string& f5, const std::string& f6);

		void Bind(const GLenum& textureUnit) const;

		GLuint getTextureID(void) const;

	private:
		void decodeTextureFile(const std::string& m_filename);

		TextureData *t_data;
		GLenum m_textureTarget;
		GLuint m_textureID;
	};
}
#endif
