#include "GraphicEngine.h"

#include "ShaderFiles.h"

#include "World.h"
#include "CameraC.h"

#include "GLFW_Window.h"
#include "ModelLibrary.h"
#include "TextureLibrary.h"
#include "Mesh.h"

#include "gbuffer.h"
#include "ssaobuffer.h"
#include "pbuffer.h"
#include "pingpongFBO.h"
#include "skyboxbuffer.h"
#include "finalFBO.h"
#include "depthMapFBO.h"

#include "engine_common.h"

#include "DirLightC.h"

#include "MyMath.h"

#include "GraphicScale.h"

#include "DebugMesh.h"

#include "SphereColliderC.h"
#include "AABB.h"

#include "Texture.h"

#include "PlayerManager.h"

#include "LineMesh.h"

#include "ComponentsPool.h"

namespace pp
{
	GraphicEngine* GraphicEngine::s_instance = nullptr;

	void GraphicEngine::setUp(void)
	{
		// shade stuff
		ShaderHeaven* shandle = ShaderHeaven::getInstance();

		// UBO init
		ubo = shandle->matricesubo;

		// simple shader
		simpleshader = shandle->simpleshader;
		// geometry pass shader
		geoshader = shandle->geoshader;
		// grass shader 
		grassshader = shandle->grassshader;
		// ssao shader
		ssaoshader = shandle->ssaoshader;
		// ssao blur
		ssaoblurshader = shandle->ssaoblurshader;
		// dirlight
		lightshader = shandle->lightshader;
		// postprocessing 
		pppassshader = shandle->pppassshader;
		// lensflare pp
		lensflareshader = shandle->lensflareshader;
		// gausian blur
		blurshader = shandle->blurshader;
		// final shader
		finalshader = shandle->finalshader;
		// skybox shader
		skyboxshader = shandle->skyboxshader;
		// motion blur shader
		motionblurshader = shandle->motionblurshader;
		// fxaashader
		fxaashader = shandle->fxaashader;
		// depth shader
		depthshader = shandle->depthshader;
		// null shader 
		nullshader = shandle->nullshader;
		// debug shader
		debugshader = shandle->debugshader;

		commonshader = shandle->commonshader;

		// all fbo init
		initFBO();

		// some graphics init set up
		glDisable(GL_FRAMEBUFFER_SRGB);

		wireframe = false;
	}

	void GraphicEngine::setGoption(GraphicScale * goption)
	{
		this->goption = goption;
	}

	void GraphicEngine::initFBO(void)
	{
		// prevent memory leak
		clearBuffer();

		gbuff = new gbuffer();
		gbuff->Init(goption->getResolution().x, goption->getResolution().y);

		skyboxbuff = new skyboxbuffer();
		skyboxbuff->Init(gbuff->ResolutionX, gbuff->ResolutionY);

		finalbuff = new finalFBO();
		finalbuff->Init(gbuff->ResolutionX, gbuff->ResolutionY);

		blurbuff[FXAA] = new pingpongFBO();
		blurbuff[FXAA]->Init(gbuff->ResolutionX, gbuff->ResolutionY);

		ssaobuff = new ssaobuffer();
		ssaobuff->Init(gbuff->ResolutionX, gbuff->ResolutionY, goption->getssaoKernel());

		pbuff = new pbuffer();
		pbuff->Init(gbuff->ResolutionX / 4, gbuff->ResolutionY / 4);

		depthbuff = new depthMapFBO();
		depthbuff->Init(goption->getShadowResolution().x, goption->getShadowResolution().y);

		for (int i = 0; i < FXAA; ++i) // except fxaa
		{
			blurbuff[i] = new pingpongFBO();
			blurbuff[i]->Init(pbuff->ResolutionX, pbuff->ResolutionY);
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		gbuff->BindFinalTex();
		gbuff->BindDiffuseTex();
		gbuff->BindNormalTex();
		gbuff->BindPositionTex();
		gbuff->BindPositionViewTex();	
		gbuff->BindNormalViewTex();
		gbuff->BindVelTex();
		ssaobuff->BindNoiseTex();	
		ssaobuff->BindSSAOColorBlur();
		ssaobuff->BindSSAOColorTex();
		pbuff->BindBrightnessTex();
		pbuff->BindLensFlareTex();
		pbuff->BindLowResTex();
		blurbuff[BLOOM_BLUR]->bindTex(BLOOM_BLUR_TEXTURE_UNIT0, 0);
		blurbuff[BLOOM_BLUR]->bindTex(BLOOM_BLUR_TEXTURE_UNIT1, 1);
		blurbuff[LENSF_BLUR]->bindTex(LENSF_BLUR_TEXTURE_UNIT0, 0);
		blurbuff[LENSF_BLUR]->bindTex(LENSF_BLUR_TEXTURE_UNIT1, 1);
		blurbuff[LOWRES_BLUR]->bindTex(LOWRESBLUR_TEXTURE_UNIT0, 0);
		blurbuff[LOWRES_BLUR]->bindTex(LOWRESBLUR_TEXTURE_UNIT1, 1);
		TextureLibrary::getInstance()->diffMap["LENSCOLOR"]->Bind(LENSFLARE_COLOR_TEXTURE_UNIT);
		TextureLibrary::getInstance()->diffMap["LENSDIRT"]->Bind(LENSDIRT_COLOR_TEXTURE_UNIT);
		TextureLibrary::getInstance()->diffMap["LENSSTAR"]->Bind(LENSSTAR_COLOR_TEXTURE_UNIT);
		TextureLibrary::getInstance()->diffMap["SKYBOX_HILLS"]->Bind(SKYBOX_TEXTURE_UNIT);
		skyboxbuff->BindFinalTex();
		finalbuff->bindMotionBlurTex();
		finalbuff->bindFinalTex();
		blurbuff[FXAA]->bindTex(FXAA_TEXTURE_UNIT0,0);
		blurbuff[FXAA]->bindTex(FXAA_TEXTURE_UNIT1,1);
		depthbuff->bindDepthMap(DEPTH_TEXTURE_UNIT);


	}

	void GraphicEngine::ShadersEarlySetUp(void) const
	{
		geoshader->Start();
		geoshader->load_DepthTex(DEPTH_TEXTURE_UNIT_INDEX);
		geoshader->Stop();

		// shaders additional set up
		ssaoshader->Start();
		ssaoshader->load_SampleKernel(ssaobuff->ssaoKernel);
		ssaoshader->load_ScreenSize(static_cast<float>(ssaobuff->ResolutionX) / 4.f, static_cast<float>(ssaobuff->ResolutionY) / 4.f);  // hardcode
		ssaoshader->load_TextureUnit(POSITION_VIEW_TEXTURE_UNIT_INDEX, NORMAL_VIEW_TEXTURE_UNIT_INDEX, NOISE_TEXTURE_UNIT_INDEX);
		ssaoshader->load_KernelSize(goption->getssaoKernel());
		ssaoshader->load_Strength(goption->getssaoStrength());
		ssaoshader->load_Radius(goption->getssaoRadius());
		ssaoshader->Stop();

		ssaoblurshader->Start();
		ssaoblurshader->load_SSAOTexUnit(SSAO_TEXTURE_UNIT_INDEX);
		ssaoblurshader->Stop();

		lightshader->Start();
		lightshader->load_ALLGPASS(POSITION_TEXTURE_UNIT_INDEX, NORMAL_TEXTURE_UNIT_INDEX, DIFF_TEXTURE_UNIT_INDEX, SSAOBLUR_TEXTURE_UNIT_INDEX);
		lightshader->load_ScreenSize((float)gbuff->ResolutionX, (float)gbuff->ResolutionY);
		lightshader->load_SkyboxUnit(SKYBOXFBO_TEXTURE_UNIT_INDEX);
		lightshader->Stop();

		motionblurshader->Start();
		motionblurshader->load_ALLTexUnit(FXAA_TEXTURE_UNIT_INDEX1, VEL_TEXTURE_UNIT_INDEX);
		motionblurshader->load_MaxSample(goption->getmotionblur_maxsample());
		motionblurshader->Stop();

		pppassshader->Start();
		pppassshader->load_TextureUnit(MOTIONBLURFBO_TEXTURE_UNIT_INDEX);
		pppassshader->load_BiasAndScale(goption->getlensFBias(), goption->getlensFScale());
		pppassshader->Stop();

		lensflareshader->Start();
		lensflareshader->load_TexUnit(BRIGHTNESS_TEXTURE_UNIT_INDEX, LENSFLARE_COLOR_TEXTURE_UNIT_INDEX);
		lensflareshader->load_Distortion(goption->getlensFDistortion());
		lensflareshader->load_GhostDispersal(goption->getlensFGhostDispersal());
		lensflareshader->load_HaloWidth(goption->getlensFHaloWidth());
		lensflareshader->load_NumOfGhost(goption->getlensFGhost());
		lensflareshader->Stop();

		// blur shader init
		blurshader->Start();
		blurshader->load_BlurDirection(1.f, 0.f);
		blurshader->load_BlurRadius(goption->getblurRadius()); // this one need to adjust for better framerate
		blurshader->load_TexUnit(BRIGHTNESS_TEXTURE_UNIT_INDEX); // will switch depends on situation
		blurshader->Stop();


		finalshader->Start();
		finalshader->load_TextureUnit(MOTIONBLURFBO_TEXTURE_UNIT_INDEX);
		finalshader->load_BloomTextureUnit(BLOOM_BLUR_TEXTURE_UNIT_INDEX1);
		finalshader->load_LensFlareTextureUnit(LENSF_BLUR_TEXTURE_UNIT_INDEX1);
		finalshader->load_LensPostProcess(LENSDIRT_COLOR_TEXTURE_UNIT_INDEX, LENSSTAR_COLOR_TEXTURE_UNIT_INDEX);
		finalshader->load_BloomEnable(goption->isbloomEnable());
		finalshader->load_LensFlareEnable(goption->islensFEnable());
		finalshader->Stop();

		fxaashader->Start();
		fxaashader->load_FrameBufferSize((float)gbuff->ResolutionX, (float)gbuff->ResolutionY);
		fxaashader->load_TexUnit(FINALFINAL_TEXTURE_UNIT_INDEX);
		fxaashader->Stop();
	}
	
	void GraphicEngine::ShadersUpdate(void) const
	{
		if (goption->ismotionBlurEnable())
		{
			motionblurshader->Start();
			motionblurshader->load_InputTex(FINAL_TEXTURE_UNIT_INDEX);
			motionblurshader->Stop();

			pppassshader->Start();
			pppassshader->load_TextureUnit(MOTIONBLURFBO_TEXTURE_UNIT_INDEX);
			pppassshader->Stop();

			if (goption->islow_resblurenable())
			{
				finalshader->Start();
				finalshader->load_TextureUnit(LOWRESBLUR_TEXTURE_UNIT_INDEX1);
				finalshader->Stop();
			}
			else
			{
				finalshader->Start();
				finalshader->load_TextureUnit(MOTIONBLURFBO_TEXTURE_UNIT_INDEX);
				finalshader->Stop();
			}
		}

		else
		{
			pppassshader->Start();
			pppassshader->load_TextureUnit(FINAL_TEXTURE_UNIT_INDEX);
			pppassshader->Stop();

			if (goption->islow_resblurenable())
			{
				finalshader->Start();
				finalshader->load_TextureUnit(LOWRESBLUR_TEXTURE_UNIT_INDEX1);
				finalshader->Stop();
			}
			else
			{
				finalshader->Start();
				finalshader->load_TextureUnit(FINAL_TEXTURE_UNIT_INDEX);
				finalshader->Stop();
			}
		}

		simpleshader->Start();
		goption->isfxaa_enable() ? simpleshader->load_TexUnit(FXAA_TEXTURE_UNIT_INDEX1) : simpleshader->load_TexUnit(FINALFINAL_TEXTURE_UNIT_INDEX);
		simpleshader->Stop();
	}

	void GraphicEngine::update(const float & dt)
	{
		if (goption->isFlaged())
		{
			ssaobuff->regenerateKernel(goption->getssaoKernel());
			ShadersEarlySetUp();
			ShadersUpdate();
			goption->setUpdateFlag(false);
		}

		goption->setcurrentFPS(1.f / dt);
	}

	void GraphicEngine::render(const World& world) const
	{
		CameraC& cam = *world.renderCam;

		// update all for once
		ubo->updateALL(cam.getView(), cam.getProjection());
		goption->calcLensFlareMat(cam);

		// some opengl important setting
		glEnable(GL_DEPTH_TEST);

		// Only the geometry pass or shadow pass updates the depth buffer
		// depth test enable and setting
		glDepthMask(GL_TRUE);

		// disable cull face for all geometry 
		glEnable(GL_CULL_FACE);

		// shadow pass
		shadowPass(world);
		
		// beginning of greatness
		gbuff->startFrame();

		// geometry pass baby
		GeometryPass(world); // velocity buffer also generated from now

		// skybox render
		SkyboxPass(world);

		// ssao
		if (goption->isssaoEnable())
		{
			SSAOPostProcess();
		}

		// light pass
		DeferredLightsPass(world, cam.position);

		// now only quad is allowed to render
		quad->bindVertexArray();

		// motion blur
		if (goption->ismotionBlurEnable())
		{
			motionBlurPass();
		}

		// beggining of post processing baby
		pbuff->startFrame();

		// post process
		PostProcessingPass();

		// final render on screen
		FinalPass();

		// rmb the quad??
		glBindVertexArray(0);


		// RENDER FINISH !!!!
		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////
	//						all the Rendering helpers Functions below							 ///
	//						all the PostProcess helpers Functions also below					 ///
	////////////////////////////////////////////////////////////////////////////////////////////////

	void GraphicEngine::shadowPass(const World & world) const
	{
		depthbuff->prepareForDrawing();

		depthshader->Start();
		depthshader->load_LightSpaceMatrix(world.getDirLight()->getLightSpace());
		world.renderMeshDepthPASS();
		playerHandle->drawDepth();
		depthshader->Stop();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::GeometryPass(const World & world) const
	{
		// color buffer drawing setting start
		gbuff->PrepareForGeoPassDrawing();

		// color buffer and depth clearing
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// start the Gpass shader
		geoshader->Start();
		// geometry shader calc shadow responsible
		geoshader->load_LightMatrix(world.getDirLight()->getLightSpace());
		// the world shld have this shader 
		world.renderMeshGPASS();
		playerHandle->draw();
		// lastly close the shader to finish gpass
		geoshader->Stop();

		//// start the grass shader
		//grassshader->Start();
		//grassshader->load_Timer(timer);
		//grassshader->load_WindDir(dir);
		//// render all the grass into gpass
		//world.renderGrassGPASS();
		//// stop it baby
		//grassshader->Stop();

		// When we get here the depth buffer is already populated and the stencil pass
		// depends on it, but it does not write to it.
		glDepthMask(GL_FALSE);

		// unbind the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::SkyboxPass(const World &world) const
	{
		// Copy content of geometry's depth buffer to skybox framebuffer's depth buffer
		gbuff->readBuff();
		skyboxbuff->receiveBuff();

		// Draw skybox as last
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content

		// render line here
		commonshader->Start();
		commonshader->load_color(vec3f(0.1f, 1.0f, 2.0f));
		commonshader->load_ModelMatrix(mat4f());
		playerHandle->renderLine();
		commonshader->Stop();

		if (skyboxEnable)
		{
			// render something
			skyboxshader->Start();
			skybox->Render();
			skyboxshader->Stop();
		}
		

		glDepthFunc(GL_LESS); // Set depth function back to default
		glDepthMask(GL_FALSE);
		// depth test disable
		
		

		bool meshcollider = goption->isDebugMeshRenderMesh();
		bool ellipsoidcollider = goption->isDebugMeshRenderEllipsoid();

		if (meshcollider || ellipsoidcollider)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			commonshader->Start();

			if (meshcollider)
			{
				world.renderMeshColliders();
				playerHandle->allComponents->renderMeshCollider();
			}

			if (ellipsoidcollider)
			{
				world.renderEllipsoidColliders();
				playerHandle->allComponents->renderEllipsoidCollider();
			}

			commonshader->Stop();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (goption->isDebugMeshRenderSphere() || goption->isDebugMeshRenderAABB())
		{
			// debug drawing
			world.renderDebugMesh();
			playerHandle->allComponents->renderAABB();
			playerHandle->allComponents->renderSphereCollider();

			debugshader->Start();
			debugshader->load_color(vec3f(2.0f, 1.0f, 0.25f));
			if (SphereColliderC::modelMats.size() > 0 && goption->isDebugMeshRenderSphere()) spheredebug->RenderInstanced(SphereColliderC::modelMats);
			if (AABB::modelMats.size() > 0 && goption->isDebugMeshRenderAABB()) AABBdebug->RenderInstanced(AABB::modelMats);
			debugshader->Stop();

			SphereColliderC::modelMats.clear();
			AABB::modelMats.clear();
		}


		// render collectable here
		world.renderAllCollectable();

		glDisable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::SSAOPostProcess(void) const
	{
		// all of them is using quad to render 
		quad->bindVertexArray();

		// SSAO
		SSAOPass();

		// BLUR SSAO
		SSAOBlur();

		// rmb the quad??
		glBindVertexArray(0);
	}

	void GraphicEngine::SSAOPass(void) const
	{
		ssaobuff->BindSSAOBuff();
		ssaoshader->Start();
		
		// render quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		ssaoshader->Stop();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::SSAOBlur(void) const
	{
		ssaobuff->BindSSAOBlurBuff();
		ssaoblurshader->Start();
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		ssaoblurshader->Stop();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	}

	void GraphicEngine::DeferredLightsPass(const World & world, const vec3f& viewPos) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind fbo
		gbuff->PreBindForLightPass();

		// light volume set up
		LightVolume->bindVertexArray();
		const static GLuint lightvolumesize = LightVolume->getIndexSize();

		// stencil pass first before point light
		// From here ------------------------------------------------------------------------------------------------------------------------------------
		StencilPassSetting();

		nullshader->Start();
		// render light volume here pls
		world.renderLightVolume(false);
		nullshader->Stop();

		// till here ------------------------------------------------------------------------------------------------------------------------------------

		// after stencil pass .. set up the gl state before rendering point light and dir light
		LightGLStateSetting();
		
		// shader just for light calc only
		lightshader->Start();
		lightshader->load_ViewPos(viewPos);
		lightshader->load_SSAOEnable(goption->isssaoEnable());
		
		// point light pass 
		// From here ------------------------------------------------------------------------------------------------------------------------------------
		// stencil setting
		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		// only cull front face
		glCullFace(GL_FRONT);

		lightshader->load_LightType(1); // tell the shader that this is point light

		// render all point lights here
		world.renderLightVolume(true);

		// change to cull face back 
		glCullFace(GL_BACK);

		// The directional light does not need a stencil test because its volume is unlimited.
		// stencil disable here
		glDisable(GL_STENCIL_TEST);

		// light volume is useless alr
		glBindVertexArray(0);

		// till here ------------------------------------------------------------------------------------------------------------------------------------

		// directional pass
		lightshader->load_LightType(0); // tell the shader that this is directional light
		quad->Render();

		// rmb to reset blending option
		glDisable(GL_BLEND);

		// lastly stop the shader
		lightshader->Stop();

		// rmb to unbind all the texture before move on to the next rendering stage
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::StencilPassSetting(void) const
	{
		// We need stencil to be enabled in the stencil pass to get the stencil buffer
		// updated and we also need it in the light pass because we render the light
		// only if the stencil passes.
		// stencil enable here
		glEnable(GL_STENCIL_TEST);

		// must disable the draw buffers 
		glDrawBuffer(GL_NONE);

		// depth test enable
		glEnable(GL_DEPTH_TEST);

		// cull face disable
		glDisable(GL_CULL_FACE);

		// rmb to clear all stencil before passing it
		glClear(GL_STENCIL_BUFFER_BIT);

		// We need the stencil test to be enabled but we want it
		// to succeed always. Only the depth test matters.
		// stencil setting
		glStencilFunc(GL_ALWAYS, 0, 0);
		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

	}

	void GraphicEngine::LightGLStateSetting(void) const
	{
		// attach and bind all the gbuffer textures for the shader to calc lights
		// then draw it to the final texture
		gbuff->PrepareForLightPass();

		// depth test disable
		glDisable(GL_DEPTH_TEST);

		// cull face enable
		glEnable(GL_CULL_FACE);

		// blending enable and setting
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		
	}

	void GraphicEngine::motionBlurPass(void) const
	{
		finalbuff->prepareMotionBlurPass();

		motionblurshader->Start();
		motionblurshader->load_VelocityScale(goption->getcurrentFPS() * goption->getmotionblur_framerate());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		motionblurshader->Stop();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::PostProcessingPass(void) const
	{
		pbuff->prepareAttachments();

		// prepare low res, brightness texture .. 
		pppassshader->Start();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		pppassshader->Stop();

		// lens flare pass
		if (goption->islensFEnable())
		{
			// generate lens flare texture
			LensFlarePass();
		}

		// blur lens flare effect here .. take the lensflare tex from pbuff
		// post process bloom stage
		BlurPass();

		// last LOD

		// rmb to unbind all the texture before move on to the next rendering stage
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GraphicEngine::LensFlarePass(void) const
	{
		pbuff->drawForLensflare();

		lensflareshader->Start();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		lensflareshader->Stop();
	}

	// small helper function to check .. if it is not equal, will return 0.f
	float when_eq(float x, float y)
	{
		return 1.0f - abs((x - y));
	}

	void GraphicEngine::BlurPass(void) const
	{
		// init state before go into the loop
		float x = 0.f; float y = 1.f;
		GLboolean horizontal = true, first_iteration = true;

		blurshader->Start();

		for (int i = 0; i < goption->getblurSize(); i++)
		{
			blurshader->load_BlurDirection(x, y);

			if (goption->isbloomEnable())
			{
				// for bloom
				blurbuff[BLOOM_BLUR]->bindFBO(horizontal);
				first_iteration ? blurshader->load_TexUnit(BRIGHTNESS_TEXTURE_UNIT_INDEX) : blurshader->load_TexUnit(BLOOM_BLUR_TEXTURE_UNIT_INDEX0 + !horizontal);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
			if (goption->islensFEnable())
			{
				// for lensflare blur
				blurbuff[LENSF_BLUR]->bindFBO(horizontal);
				first_iteration ? blurshader->load_TexUnit(LENSFLARE_TEXTURE_UNIT_INDEX) : blurshader->load_TexUnit(LENSF_BLUR_TEXTURE_UNIT_INDEX0 + !horizontal);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
			if (goption->islow_resblurenable())
			{
				// for lowres blur
				blurbuff[LOWRES_BLUR]->bindFBO(horizontal);
				first_iteration ? blurshader->load_TexUnit(LOWRES_TEXTURE_UNIT_INDEX) : blurshader->load_TexUnit(LOWRESBLUR_TEXTURE_UNIT_INDEX0 + !horizontal);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			// prepare for next loop
			horizontal = !horizontal;

			// one of the way to reduce if else statement in for loop
			y = 1.f - when_eq(y, 1.f);
			x = 1.f - y;

			if (first_iteration)
			{
				first_iteration = false;
			}
		}

		blurshader->Stop();
	}

	void GraphicEngine::FinalPass(void) const
	{
		// do hdr and tone mapping .. gather everything
		finalbuff->prepareFinalPass();
		finalshader->Start();
		finalshader->load_LensStartMatrix(goption->getlensflareMat());
		finalshader->load_FadeValue(goption->getFadeValue());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		finalshader->Stop();
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		// fxaa after tone mapping
		if (goption->isfxaa_enable())
		{
			fxaaPass();
		}

		// let the default framebuffer do the job
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, windowHandle->getWindowWidth(), windowHandle->getWindowHeight()); // window size here

		// gamma correction do here
		simpleshader->Start();
		goption->isfxaa_enable() ? simpleshader->load_TexUnit(FXAA_TEXTURE_UNIT_INDEX1) : simpleshader->load_TexUnit(FINALFINAL_TEXTURE_UNIT_INDEX);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		simpleshader->Stop();
	}

	void GraphicEngine::fxaaPass(void) const
	{
		bool change = false;
		bool first_iteration = true;
		blurbuff[FXAA]->viewPortUpdate();
		for (int i = 0; i < goption->getfxaa_Size(); ++i)
		{
			blurbuff[FXAA]->bindFBO(i);

			fxaashader->Start();
			first_iteration ? fxaashader->load_TexUnit(FINALFINAL_TEXTURE_UNIT_INDEX) : blurshader->load_TexUnit(FXAA_TEXTURE_UNIT_INDEX0 + change);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			fxaashader->Stop();

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			change = !change;
			if (first_iteration)
			{
				first_iteration = false;
			}
		}
	}

	void GraphicEngine::clearBuffer(void)
	{
		if (gbuff != nullptr)
		{
			
			delete gbuff;
			gbuff = nullptr;
		}

		if (ssaobuff != nullptr)
		{
			ssaobuff->cleanUp();
			delete ssaobuff;
			ssaobuff = nullptr;
		}

		if (pbuff != nullptr)
		{
			
			delete pbuff;
			pbuff = nullptr;
		}

		for (int i = 0; i < LAST_NORM; ++i)
		{
			if (blurbuff[i] != nullptr)
			{
				blurbuff[i]->clear();
				delete blurbuff[i];
				blurbuff[i] = nullptr;
			}
		}

		if (skyboxbuff != nullptr)
		{
			delete skyboxbuff;
			skyboxbuff = nullptr;
		}

		if (finalbuff != nullptr)
		{
			delete finalbuff;
			finalbuff = nullptr;
		}

		if (depthbuff != nullptr)
		{
			depthbuff->clear();
			delete depthbuff;
			depthbuff = nullptr;
		}
	}

	void GraphicEngine::resetShadowMap(void)
	{
		depthbuff->clear();
		delete depthbuff;
		depthbuff = nullptr;

		depthbuff = new depthMapFBO();
		depthbuff->Init(goption->getShadowResolution().x, goption->getShadowResolution().y);

		depthbuff->bindDepthMap(DEPTH_TEXTURE_UNIT);
	}

	GraphicEngine::GraphicEngine(void) : ubo(nullptr), geoshader(nullptr), gbuff(nullptr), windowHandle(nullptr), 
		quad(nullptr), grassshader(nullptr), goption(nullptr), ssaobuff(nullptr), lightshader(nullptr), pbuff(nullptr), lensflareshader(nullptr),
		skyboxbuff(nullptr), skybox(nullptr), finalbuff(nullptr), fxaashader(nullptr), simpleshader(nullptr), depthbuff(nullptr),
		depthshader(nullptr), AABBdebug(nullptr), playerHandle(nullptr), skyboxEnable(true)
	{
		windowHandle = GLFW_Window::getInstance();
		quad = ModelLibrary::getInstance()->models["QUAD"];
		skybox = ModelLibrary::getInstance()->models["CUBEIN"];
		LightVolume = ModelLibrary::getInstance()->models["LIGHTVOLUME"];
		spheredebug = dynamic_cast<DebugMesh*>(ModelLibrary::getInstance()->models["SPHEREDEBUG"]);
		AABBdebug = dynamic_cast<DebugMesh*>(ModelLibrary::getInstance()->models["CUBEDEBUG"]);
		ZERO_MEM(blurbuff);
		playerHandle = PlayerManager::getInstance();
	}

	GraphicEngine::~GraphicEngine(void)
	{
		clearBuffer();

		delete goption;
		goption = nullptr;
	}

}