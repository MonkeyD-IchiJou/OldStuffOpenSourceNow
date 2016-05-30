#include "MeshRendererC.h"
#include "ModelLibrary.h"

#include "Mesh.h"

#include "ShaderHeaven.h"
#include "GeometryPassShader.h"
#include "Entity.h"
#include "TransformationC.h"
#include "depthShader.h"

#include "SphereColliderC.h"

namespace pp
{
	GeometryPassShader* MeshRendererC::shader = nullptr;
	depthShader* MeshRendererC::depthshader = nullptr;

	MeshRendererC::MeshRendererC(void) :
		RendererC(MESH)
	{
		if (shader == nullptr)
		{
			shader = ShaderHeaven::getInstance()->geoshader;
		}

		if (depthshader == nullptr)
		{
			depthshader = ShaderHeaven::getInstance()->depthshader;
		}
	}

	MeshRendererC::~MeshRendererC(void)
	{
		shader = nullptr;
		depthshader = nullptr;
	}

	void MeshRendererC::update(const float& dt)
	{
		if (getOwner()->isActive() && this->updatedFlag)
		{
			if (spherecollider == nullptr)
			{
				spherecollider = getOwner()->findComponentT<SphereColliderC>();
			}

			// check for valid mesh or not
			map<string, Mesh*>::iterator it = ModelLibrary::getInstance()->models.find(meshName);

			if (it == ModelLibrary::getInstance()->models.end())
			{
				printf("invalid mesh pls \n");
				throw 0;
			}

			// update the mesh 
			mesh = ModelLibrary::getInstance()->models[meshName];

			// get the handle for model matrix
			modelMatrix = &getOwner()->transformC->getFinalMat4();

			pos = &getOwner()->transformC->localPosition;

			// get the handle for prev model matrix
			prevMVPMatrix = &getOwner()->transformC->getPrevMVPMat4();

			updatedFlag = false;
		}
	}

	void MeshRendererC::draw(void) const
	{
		if (getOwner()->isActive())
		{
			if (spherecollider)
			{
				if (spherecollider->frustumCull("MESHCULL") && isVisible && enabled)
				{
					if (modelMatrix)
					{
						// material 
						shader->load_Color(color);
						shader->load_Shininess(shininess);
						shader->load_Emissive(emissive);

						// matrix
						shader->load_ModelMatrix(*modelMatrix);
						shader->load_PrevModelViewProjectionMatrix(*prevMVPMatrix);

						mesh->Render();
					}
				}
			}

			else
			{
				if (isVisible && enabled)
				{
					if (modelMatrix)
					{
						// material 
						shader->load_Color(color);
						shader->load_Shininess(shininess);
						shader->load_Emissive(emissive);

						// matrix
						shader->load_ModelMatrix(*modelMatrix);
						shader->load_PrevModelViewProjectionMatrix(*prevMVPMatrix);

						mesh->Render();
					}
				}
			}
		}
	}

	void MeshRendererC::drawDepth(void) const
	{
		if (getOwner()->isActive())
		{
			if (isVisibleDepth && enabled)
			{
				if (modelMatrix)
				{
					depthshader->load_ModelMatrix(*modelMatrix);
					// draw
					mesh->Render();
				}
			}
		}
	}

	void MeshRendererC::save(ofstream & myFile, const unsigned int & guid)
	{
		myFile << "Entity.addMeshRenderer(" << guid << ") \n";

		myFile << "Entity.getMeshRenderer.setName(" << guid << ", '" << meshName << "') \n";
		myFile << "Entity.getMeshRenderer.setColor(" << guid << ", " << color << ") \n";
		myFile << "Entity.getMeshRenderer.setShininess(" << guid << ", " << shininess << ") \n";
		myFile << "Entity.getMeshRenderer.setEmissive(" << guid << ", " << emissive << ") \n";
	}


}
