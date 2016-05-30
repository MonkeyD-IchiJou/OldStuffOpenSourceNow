#include "DirLightC.h"
#include "ShaderHeaven.h"
#include "LightShader.h"
#include "GeometryPassShader.h"

#include "Entity.h"
#include "TransformationC.h"
#include "CameraC.h"
#include "MeshRendererC.h"

namespace pp
{
	LightShader * DirLightC::shader = nullptr;
	GeometryPassShader * DirLightC::gshader = nullptr;

	double DirLightC::lightprojsize = 12;
	DirLightC::DirLightC(void) : LightC(directionalLight),
		near_plane(0.1),
		far_plane(500.0)
	{
		if (shader == nullptr)
		{
			shader = ShaderHeaven::getInstance()->lightshader;
			gshader = ShaderHeaven::getInstance()->geoshader;
		}

		lightProjection.SetToIdentity();
		lightView.SetToIdentity();

		LightProjectionUpdate();
	}


	DirLightC::~DirLightC(void)
	{
		shader = nullptr;
	}

	void DirLightC::update(const float& dt)
	{
		if (updatedFlag)
		{
			getOwner()->transformC->position = (-lightdirection * ((float)far_plane / 2.f));
			getOwner()->transformC->updatedFlag = true;

			shader->Start();
			shader->load_DirLight(*this);
			shader->Stop();

			gshader->Start();
			gshader->load_LightDir(-lightdirection);
			gshader->Stop();

			MeshRendererC* m = getOwner()->findComponentT<MeshRendererC>();
			if (m != nullptr)
			{
				m->color = this->lightColor;
			}

			LightProjectionUpdate();

			updatedFlag = false;
		}
	}

	void DirLightC::LightProjectionUpdate(void)
	{
		lightProjection.SetToIdentity();
		lightProjection.SetToOrtho(-lightprojsize, lightprojsize, -lightprojsize, lightprojsize, near_plane, far_plane);
	}

	void DirLightC::LightLookAtUpdate(const float & dt, const CameraC& cam)
	{
		lightPos = -lightdirection * ((float)far_plane / 2.f);
		lightup = lightdirection.cross(vec3f(1.f, 0, 0));

		vec3f dir = cam.lookingDir;
		dir.y = 0;

		if(dir.lengthSquared() > 2.f)
 			dir.normalize();
		
		float dist = static_cast<float>(lightprojsize / 2.0);
		lightView.SetToIdentity();
		lightView.SetToLookAt(cam.target + lightPos + dir * dist, cam.target + dir * dist, lightup);
	}

	void DirLightC::changeLightDir(const vec3f & axisRotate, const float & angle)
	{
		Quaternion q(angle, axisRotate);
		lightdirection = q * lightdirection;

		// change the light dir
		updatedFlag = true;
	}

	mat4f DirLightC::getLightSpace(void) const
	{
		return lightProjection * lightView;
	}

	void DirLightC::abstractclass(void)
	{
	}

	void DirLightC::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.addDirLight(" << guid << ") \n";

		myFile << "Entity.getDirLight.setAmbient(" << guid << ", " << ambient << ") \n";
		myFile << "Entity.getDirLight.setDiffuse(" << guid << ", " << diffuse << ") \n";
		myFile << "Entity.getDirLight.setSpecular(" << guid << ", " << specular << ") \n";
		myFile << "Entity.getDirLight.setLightColor(" << guid << ", " << lightColor << ") \n";
		myFile << "Entity.getDirLight.setLightDirection(" << guid << ", " << lightdirection << ") \n";
	}

}
