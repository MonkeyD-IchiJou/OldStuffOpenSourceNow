#ifndef GBUFFER_H
#define GBUFFER_H

#include "GLH.h"

namespace pp
{

	class gbuffer
	{
	public:

		enum GBUFFER_TEXTURE_TYPE
		{
			GBUFFER_TEXTURE_TYPE_POSITION,
			GBUFFER_TEXTURE_TYPE_NORMAL,
			GBUFFER_TEXTURE_TYPE_DIFFUSE,
			GBUFFER_TEXTURE_TYPE_NORMAL_VIEW,
			GBUFFER_TEXTURE_TYPE_POSITION_VIEW,
			GBUFFER_TEXTURE_TYPE_VELOCITY,
			GBUFFER_NUM_TEXTURES
		};

		gbuffer(void);
		~gbuffer(void);

		// init all the gbuff textures
		bool Init(const int & rx, const int& ry);

		// begin gpass
		void startFrame(void) const;

		// first prepare to extract gpass info 
		void PrepareForGeoPassDrawing(void) const;
		void PrepareForLightPass(void) const;
		void PreBindForLightPass(void) const;
		void readBuff(void) const;

		// all texture binding
		void BindPositionTex(void) const;
		void BindNormalTex(void) const;
		void BindDiffuseTex(void) const;
		void BindPositionViewTex(void) const;
		void BindNormalViewTex(void) const;
		void BindVelTex(void) const;
		void BindFinalTex(void) const;

		// get and setter
		GLuint getPostexture(void) const;
		GLuint getNormtexture(void) const;
		GLuint getDifftexture(void) const;
		GLuint getNormViewtexture(void) const;
		GLuint getPosViewtexture(void) const;
		GLuint getVeltexture(void) const;
		GLuint getFinaltexture(void) const;

		int ResolutionX, ResolutionY;

	private:
		void clear();

		GLuint m_fbo;
		GLuint rboDepth;
		GLuint m_textures[GBUFFER_NUM_TEXTURES];
		GLuint m_finalTexture;
	};
}

#endif
