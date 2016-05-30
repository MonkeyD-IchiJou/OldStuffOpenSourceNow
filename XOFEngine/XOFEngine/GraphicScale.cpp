#include "GraphicScale.h"
#include "CameraC.h"

namespace pp
{
	GraphicScale::GraphicScale(void) : bloomEnable(true),
		blurRadius(16),
		blurSize(16),
		lensFScale(-0.6f),
		lensFBias(5.5f),
		lensFDistortion(3.5f),
		lensFEnable(true),
		lensFGhost(8),
		lensFGhostDispersal(0.26f),
		lensFHaloWidth(0.6f),
		ssaoKernel(16),
		ssaoRadius(1.5f),
		ssaoStrength(3.f),
		motionblur_maxsample(128),
		motionBlurEnable(true),
		ssaoEnable(true),
		motionblur_framerate(1.f / 60.f),
		fxaa_enable(true),
		low_resblurenable(false),
		fxaa_Size(2),
		currentFPS(60.f),
		updateFlag(true),
		DebugMeshRenderSphere(false),
		DebugMeshRenderAABB(false),
		DebugMeshRenderMesh(false),
		DebugMeshRenderEllipsoid(false),
		fadevalue(2.f)
	{
		resolution.Set(1280, 720);
		shadowResolution.Set(1280, 1280);
	}

	GraphicScale::~GraphicScale(void)
	{
	}

	void GraphicScale::calcLensFlareMat(const CameraC & cam)
	{

		lensflareMat.SetToIdentity();

		vec3f camx, camz;
		mat4f viewmat;
		viewmat = cam.getView();

		camx.x = viewmat.a[0];
		camx.y = viewmat.a[4];
		camx.z = viewmat.a[8];

		camz.x = viewmat.a[1];
		camz.y = viewmat.a[5];
		camz.z = viewmat.a[9];

		float camrot = camx.dot(vec3f(0, 0, 1)) + camz.dot(vec3f(0, 1, 0));

		mat4f scaleBias1(
			2.0f, 0.0f, -1.0f, 0.f,
			0.0f, 2.0f, -1.0f, 0.f,
			0.0f, 0.0f, 1.0f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
		mat4f rotation(
			cos(camrot), -sin(camrot), 0.0f, 0.f,
			sin(camrot), cos(camrot), 0.0f, 0.f,
			0.0f, 0.0f, 1.0f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
		mat4f scaleBias2(
			0.5f, 0.0f, 0.5f, 0.f,
			0.0f, 0.5f, 0.5f, 0.f,
			0.0f, 0.0f, 1.0f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);

		lensflareMat = scaleBias2 * rotation * scaleBias1;
	}

}