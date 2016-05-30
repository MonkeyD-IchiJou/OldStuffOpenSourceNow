#include "ShaderFiles.h"

namespace pp
{
	ShaderHeaven* ShaderHeaven::s_instance = nullptr;

	void ShaderHeaven::start(void)
	{
		// prevent memory leak
		cleanUP();

		matricesubo = new MatricesUBO();

		simpleshader = new SimpleShader();
		geoshader = new GeometryPassShader();
		grassshader = new GrassShader();
		ssaoblurshader = new SSAOBlurShader();
		ssaoshader = new SSAOShader();
		lightshader = new LightShader();
		pppassshader = new PostProcessPassShader();
		lensflareshader = new LensFlareShader();
		blurshader = new GausianBlurShader();
		finalshader = new FinalPassShader();
		skyboxshader = new SkyboxShader();
		motionblurshader = new MotionBlurShader();
		fxaashader = new FXAAShader();
		depthshader = new depthShader();
		nullshader = new NullShader();
		fontshader = new FontShader();
		debugshader = new debugShader();
		commonshader = new commonShader();
	}

	void ShaderHeaven::cleanUP(void)
	{
		cleanUpHelper(simpleshader);
		cleanUpHelper(geoshader);
		cleanUpHelper(grassshader);
		cleanUpHelper(ssaoshader);
		cleanUpHelper(ssaoblurshader);
		cleanUpHelper(lightshader);
		cleanUpHelper(pppassshader);
		cleanUpHelper(lensflareshader);
		cleanUpHelper(blurshader);
		cleanUpHelper(finalshader);
		cleanUpHelper(skyboxshader);
		cleanUpHelper(motionblurshader);
		cleanUpHelper(fxaashader);
		cleanUpHelper(depthshader);
		cleanUpHelper(nullshader);
		cleanUpHelper(fontshader);
		cleanUpHelper(debugshader);
		cleanUpHelper(commonshader);

		if (matricesubo != nullptr)
		{
			delete matricesubo;
			matricesubo = nullptr;
		}

		simpleshader = nullptr;
		matricesubo = nullptr;
		geoshader = nullptr;
		grassshader = nullptr;
		ssaoblurshader = nullptr;
		ssaoshader = nullptr;
		lightshader = nullptr;
		pppassshader = nullptr;
		lensflareshader = nullptr;
		blurshader = nullptr;
		finalshader = nullptr;
		skyboxshader = nullptr;
		motionblurshader = nullptr;
		fxaashader = nullptr;
		depthshader = nullptr;
		nullshader = nullptr;
		fontshader = nullptr;
		debugshader = nullptr;
		commonshader = nullptr;
	}

	ShaderHeaven::ShaderHeaven(void) : 
		simpleshader(nullptr), 
		matricesubo(nullptr), 
		geoshader(nullptr), 
		grassshader(nullptr), 
		ssaoblurshader(nullptr),
		ssaoshader(nullptr), 
		lightshader(nullptr), 
		pppassshader(nullptr), 
		lensflareshader(nullptr), 
		blurshader(nullptr), 
		finalshader(nullptr),
		skyboxshader(nullptr), 
		motionblurshader(nullptr), 
		fxaashader(nullptr), 
		depthshader(nullptr), 
		nullshader(nullptr), 
		fontshader(nullptr),
		debugshader(nullptr),
		commonshader(nullptr)
	{
	}

	ShaderHeaven::~ShaderHeaven(void)
	{
	}

	void ShaderHeaven::cleanUpHelper(ShaderProgram * shader)
	{
		if (shader != nullptr)
		{
			shader->CleanUp();
			delete shader;
			shader = nullptr;
		}
	}
}
