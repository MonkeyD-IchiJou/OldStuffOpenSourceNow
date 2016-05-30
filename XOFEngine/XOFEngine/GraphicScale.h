#ifndef GRAPHIC_SCALE_H
#define GRAPHIC_SCALE_H

#include "enumc.h"
#include "MathsHeader.h"

#include <string>
#include <sstream>

namespace pp
{
	class CameraC;

	class GraphicScale
	{
	public:
		GraphicScale(void);

		~GraphicScale(void);

		void calcLensFlareMat(const CameraC& cam);

		inline bool isFlaged(void) const {return updateFlag;}
		inline void setUpdateFlag(const bool & flag) { updateFlag = flag; }

		inline bool isbloomEnable(void) { return bloomEnable; }
		inline bool islensFEnable(void) { return lensFEnable; }
		inline bool ismotionBlurEnable(void) { return motionBlurEnable; }
		inline bool isssaoEnable(void) { return ssaoEnable; }
		inline bool isfxaa_enable(void) { return fxaa_enable; }
		inline bool islow_resblurenable(void) { return low_resblurenable; }
		inline bool isDebugMeshRenderSphere(void) { return DebugMeshRenderSphere; }
		inline bool isDebugMeshRenderAABB(void) { return DebugMeshRenderAABB; }
		inline bool isDebugMeshRenderMesh(void) { return DebugMeshRenderMesh; }
		inline bool isDebugMeshRenderEllipsoid(void) { return DebugMeshRenderEllipsoid; }

		inline int getssaoKernel(void) { return ssaoKernel; }
		inline int getlensFGhost(void) { return lensFGhost; }
		inline int getblurRadius(void) { return blurRadius; }
		inline int getblurSize(void) { return blurSize; }
		inline int getmotionblur_maxsample(void) { return motionblur_maxsample; }
		inline int getfxaa_Size(void) { return fxaa_Size; }

		inline float getssaoRadius(void) { return ssaoRadius; }
		inline float getssaoStrength(void) { return ssaoStrength; }
		inline float getlensFBias(void) { return lensFBias; }
		inline float getlensFScale(void) { return lensFScale; }
		inline float getlensFGhostDispersal(void) { return lensFGhostDispersal; }
		inline float getlensFHaloWidth(void) { return lensFHaloWidth; }
		inline float getlensFDistortion(void) { return lensFDistortion; }
		inline float getmotionblur_framerate(void) { return motionblur_framerate; }
		inline float getcurrentFPS(void) { return currentFPS; }
		inline float getFadeValue(void) { return fadevalue; }

		inline vec2i getResolution(void) { return resolution; }
		inline vec2i getShadowResolution(void) { return shadowResolution; }

		inline void setbloomEnable(const bool & set) { setUpdateFlag(true); bloomEnable = set; }
		inline void setlensFEnable(const bool & set) { setUpdateFlag(true); lensFEnable = set; }
		inline void setmotionBlurEnable(const bool & set) { setUpdateFlag(true); motionBlurEnable = set; }
		inline void setssaoEnable(const bool & set) { setUpdateFlag(true); ssaoEnable = set; }
		inline void setfxaa_enable(const bool & set) { setUpdateFlag(true); fxaa_enable = set; }
		inline void setlow_resblurenable(const bool & set) { setUpdateFlag(true); low_resblurenable = set; }
		inline void setDebugMeshRenderSphere(const bool & set) { setUpdateFlag(true); DebugMeshRenderSphere = set; }
		inline void setDebugMeshRenderAABB(const bool & set) { setUpdateFlag(true); DebugMeshRenderAABB = set; }
		inline void setDebugMeshRenderMesh(const bool & set) { setUpdateFlag(true); DebugMeshRenderMesh = set; }
		inline void setDebugMeshRenderEllipsoid(const bool & set) { setUpdateFlag(true); DebugMeshRenderEllipsoid = set; }

		inline void setssaoKernel(const int & set) { setUpdateFlag(true); ssaoKernel = set; }
		inline void setlensFGhost(const int & set) { setUpdateFlag(true); lensFGhost = set; }
		inline void setblurRadius(const int & set) { setUpdateFlag(true); blurRadius = set; }
		inline void setblurSize(const int & set) { setUpdateFlag(true); blurSize = set; }
		inline void setmotionblur_maxsample(const int & set) { setUpdateFlag(true); motionblur_maxsample = set; }
		inline void setfxaa_Size(const int & set) { setUpdateFlag(true); fxaa_Size = set; }

		inline void setFadeValue(const float & set) { fadevalue = set; }

		inline void setssaoRadius(const float& set) { setUpdateFlag(true); ssaoRadius = set; }
		inline void setssaoStrength(const float& set) { setUpdateFlag(true); ssaoStrength = set; }
		inline void setlensFBias(const float& set) { setUpdateFlag(true); lensFBias = set; }
		inline void setlensFScale(const float& set) { setUpdateFlag(true); lensFScale = set; }
		inline void setlensFGhostDispersal(const float& set) { setUpdateFlag(true); lensFGhostDispersal = set; }
		inline void setlensFHaloWidth(const float& set) { setUpdateFlag(true); lensFHaloWidth = set; }
		inline void setlensFDistortion(const float& set) { setUpdateFlag(true); lensFDistortion = set; }
		inline void setmotionblur_framerate(const float& set) { setUpdateFlag(true); motionblur_framerate = set; }
		inline void setcurrentFPS(const float& set) { currentFPS = set; }

		inline void setResolution(const vec2i& resolution) { this->resolution = resolution; }
		inline void setShadowResolution(const vec2i& resolution) { this->shadowResolution = resolution; }

		inline std::string getSceneTag(void) const { return sceneTag; }
		inline void setSceneTag(const std::string &n) { sceneTag = n; }

		inline mat4f getlensflareMat(void) const { return lensflareMat; }
		
		//print to ostream
		friend std::ostream& operator<<(std::ostream& os, GraphicScale& rhs)
		{
			os << "Graphics.SSAO.Enable(" + btos(rhs.isssaoEnable()) + ")" << std::endl;
			os << "Graphics.SSAO.KernelSize(" + std::to_string(rhs.getssaoKernel()) + ")" << std::endl;
			os << "Graphics.SSAO.Radius(" + std::to_string(rhs.getssaoRadius()) + ")" << std::endl;
			os << "Graphics.SSAO.Strength(" + std::to_string(rhs.getssaoStrength()) + ")" << std::endl;
			os << "Graphics.DebugMesh.Sphere(" + btos(rhs.isDebugMeshRenderSphere()) + ")" << std::endl;
			os << "Graphics.DebugMesh.AABB(" + btos(rhs.isDebugMeshRenderAABB()) + ")" << std::endl;

			os << "Graphics.MotionBlur.Enable(" + btos(rhs.ismotionBlurEnable()) + ")" << std::endl;
			os << "Graphics.MotionBlur.MaxSample(" + std::to_string(rhs.getmotionblur_maxsample()) + ")" << std::endl;
			os << "Graphics.MotionBlur.Scale(" + std::to_string(rhs.getmotionblur_framerate()) + ")" << std::endl;

			os << "Graphics.Bloom.Enable(" + btos(rhs.isbloomEnable()) + ")" << std::endl;
			os << "Graphics.Bloom.BlurRadius(" + std::to_string(rhs.getblurRadius()) + ")" << std::endl;
			os << "Graphics.Bloom.BlurSize(" + std::to_string(rhs.getblurSize()) + ")" << std::endl;

			os << "Graphics.FXAA.Enable(" + btos(rhs.isfxaa_enable()) + ")" << std::endl;
			os << "Graphics.FXAA.Size(" + std::to_string(rhs.getfxaa_Size()) + ")" << std::endl;

			os << "Graphics.LensFlare.Enable(" + btos(rhs.islensFEnable()) + ")" << std::endl;
			os << "Graphics.LensFlare.Scale(" + std::to_string(rhs.getlensFScale()) + ")" << std::endl;
			os << "Graphics.LensFlare.Bias(" + std::to_string(rhs.getlensFBias()) + ")" << std::endl;
			os << "Graphics.LensFlare.Distortion(" + std::to_string(rhs.getlensFDistortion()) + ")" << std::endl;
			os << "Graphics.LensFlare.Ghost(" + std::to_string(rhs.getlensFGhost()) + ")" << std::endl;
			os << "Graphics.LensFlare.GhostDisperal(" + std::to_string(rhs.getlensFGhostDispersal()) + ")" << std::endl;
			os << "Graphics.LensFlare.HaloWidth(" + std::to_string(rhs.getlensFHaloWidth()) + ")" << std::endl;

			os << "Graphics.Resolution.Scene(" << rhs.getResolution() << ")" << std::endl;
			os << "Graphics.Resolution.Shadow(" << rhs.getShadowResolution() << ")" << std::endl;

			return os;
		}
		
	private:
		bool bloomEnable, lensFEnable, motionBlurEnable, ssaoEnable, fxaa_enable, low_resblurenable;
		int ssaoKernel, lensFGhost, blurRadius, blurSize, motionblur_maxsample, fxaa_Size;
		float ssaoRadius, ssaoStrength, lensFBias, lensFScale, lensFGhostDispersal, lensFHaloWidth, lensFDistortion, motionblur_framerate, currentFPS, fadevalue;
		bool DebugMeshRenderSphere, DebugMeshRenderAABB, DebugMeshRenderMesh, DebugMeshRenderEllipsoid;
		bool updateFlag;
		mat4f lensflareMat;
		std::string sceneTag;

		vec2i resolution, shadowResolution;
	};
}

#endif

