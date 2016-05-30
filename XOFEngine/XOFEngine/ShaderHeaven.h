#ifndef SHADER_HEAEN_H
#define SHADER_HEAEN_H

#include "com_decla.h"

namespace pp
{
	class ShaderHeaven
	{
	public:
		SimpleShader* simpleshader;
		GeometryPassShader* geoshader;
		GrassShader* grassshader;
		SSAOShader* ssaoshader;
		SSAOBlurShader* ssaoblurshader;
		LightShader* lightshader;
		PostProcessPassShader* pppassshader;
		LensFlareShader* lensflareshader;
		GausianBlurShader* blurshader;
		FinalPassShader* finalshader;
		SkyboxShader* skyboxshader;
		MotionBlurShader* motionblurshader;
		FXAAShader* fxaashader;
		depthShader* depthshader;
		NullShader* nullshader;
		FontShader* fontshader;
		debugShader* debugshader;
		commonShader* commonshader;

		MatricesUBO* matricesubo;

		void start(void);
		void cleanUP(void);

		// Singleton class implementation
		static inline ShaderHeaven* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new ShaderHeaven();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

	private:
		ShaderHeaven(void);
		~ShaderHeaven(void);

		void cleanUpHelper(ShaderProgram* shader);

		static ShaderHeaven* s_instance;
	};
}

#endif
