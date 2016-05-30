#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "vec3.h"
#include "mat4.h"
#include "com_decla.h"
using namespace Math;

namespace pp
{
	class World;
	class GLFW_Window;
	class Mesh;
	class DebugMesh;

	class gbuffer;
	class pbuffer;
	class ssaobuffer;
	class pingpongFBO;
	class skyboxbuffer;
	class finalFBO;
	class depthMapFBO;
	
	class GraphicScale;

	class PlayerManager;

	class GraphicEngine
	{
	public:
		
		void setUp(void);
		void setGoption(GraphicScale * goption);
		void update(const float& dt);
		void render(const World& world) const;
		void clearBuffer(void);

		void resetShadowMap(void);
		// init all the fbo for graphic stuff
		void initFBO(void);

		// Singleton class implementation
		static inline GraphicEngine* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new GraphicEngine();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != 0;
		}

		bool wireframe, skyboxEnable;


	protected:
		

		// early load up for shaders 
		void ShadersEarlySetUp(void) const;

		// update the shaders if needed
		void ShadersUpdate(void) const;

		// shadow pass first
		void shadowPass(const World& world) const;

		// geometry info pass to gbuff first
		void GeometryPass(const World& world) const;

		// ssao
		void SSAOPostProcess(void) const;
		void SSAOPass(void) const;
		void SSAOBlur(void) const;

		// deffered lighting pass 
		void DeferredLightsPass(const World& world, const vec3f& viewPos) const;
		void LightGLStateSetting(void) const;
		void StencilPassSetting(void) const;

		// skybox pass
		void SkyboxPass(const World &world) const;

		// motion blur
		void motionBlurPass(void) const;
		
		// post processing pass
		void PostProcessingPass(void) const;
		void LensFlarePass(void) const;
		void BlurPass(void) const;

		// final rendering stage
		void fxaaPass(void) const;
		void FinalPass(void) const;

		

	private:
		GLFW_Window *windowHandle;
		Mesh* quad;
		Mesh* skybox;
		Mesh* LightVolume;
		DebugMesh* spheredebug;
		DebugMesh* AABBdebug;

		MatricesUBO* ubo;

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
		debugShader* debugshader;
		commonShader* commonshader;

		enum G_BLUR
		{
			BLOOM_BLUR = 0,
			LENSF_BLUR,
			LOWRES_BLUR,
			FXAA,
			LAST_NORM
		};

		gbuffer* gbuff;
		pbuffer* pbuff;
		ssaobuffer* ssaobuff;
		pingpongFBO* blurbuff[LAST_NORM];
		skyboxbuffer* skyboxbuff;
		finalFBO* finalbuff;
		depthMapFBO* depthbuff;

		GraphicEngine(void);
		~GraphicEngine(void);

		static GraphicEngine* s_instance;

		GraphicScale* goption;

		PlayerManager* playerHandle;

	};
}
#endif

