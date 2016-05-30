#include "PointLightC.h"
#include "Entity.h"
#include "TransformationC.h"
#include "MeshRendererC.h"

#include "ShaderHeaven.h"
#include "LightShader.h"
#include "NullShader.h"

#include "SphereColliderC.h"

#include "MyMath.h"

namespace pp
{
	NullShader* PointLightC::nullshader = nullptr;
	LightShader* PointLightC::pntlightshader = nullptr;

	PointLightC::PointLightC() : 
		LightC(pointLight), 
		translationMat4(nullptr),
		spherecollider(nullptr)
	{
		if (nullshader == nullptr)
		{
			nullshader = ShaderHeaven::getInstance()->nullshader;
			pntlightshader = ShaderHeaven::getInstance()->lightshader;
		}
	}


	PointLightC::~PointLightC(void)
	{
	}

	void PointLightC::update(const float& dt)
	{
		// rmb to set the light pos equal to its transformation position
		if (updatedFlag)
		{
			if (spherecollider == nullptr)
			{
				spherecollider = getOwner()->findComponentT<SphereColliderC>();
			}

			TransformationC* t = getOwner()->transformC;
			lightPos = t->localPosition;
			translationMat4 = &t->translationMat4;

			float s = CalcPointLightBSphere();
			lightvolumescale.SetToScale(s, s, s);

			MeshRendererC* m = getOwner()->findComponentT<MeshRendererC>();
			if (m != nullptr)
			{
				m->color = this->lightColor;
				m->emissive = 1;
			}

			updatedFlag = false;
		}
	}

	void PointLightC::ShaderReadInfo(const bool & pon) const
	{
		if (getOwner()->isActive() && spherecollider)
		{
			if (spherecollider->frustumCull("MESHCULL"))
			{
				if (pon == true)
				{
					pntlightshader->load_PointLight(*this);
					if (translationMat4)
						pntlightshader->load_ModelMatrix(*translationMat4 * lightvolumescale);

				}
				else
				{
					if (translationMat4)
						nullshader->load_ModelMatrix(*translationMat4 * lightvolumescale);
				}


				// draw the light volume
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			}
		}
	}

	void PointLightC::abstractclass(void)
	{
	}

	void PointLightC::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.addPointLight(" << guid << ") \n";

		myFile << "Entity.getPointLight.setDiffuse(" << guid << ", " << diffuse << ") \n";
		myFile << "Entity.getPointLight.setSpecular(" << guid << ", " << specular << ") \n";
		myFile << "Entity.getPointLight.setLightColor(" << guid << ", " << lightColor << ") \n";
	}

	float PointLightC::CalcPointLightBSphere(void) const
	{
		float lightMax = Max(Max(lightColor.x, lightColor.y), lightColor.z);

		float constant = 1.f;
		float linear = 0.35f;
		float quadratic = 0.44f;

		float radius = (-linear + std::sqrtf(linear * linear - 4 * quadratic * (constant - (256.f / 5.f) * lightMax)))
			/
			(2 * quadratic) * 5.5f;

		return radius;
	}


}
