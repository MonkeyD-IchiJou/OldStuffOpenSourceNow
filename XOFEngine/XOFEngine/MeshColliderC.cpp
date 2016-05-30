#include "MeshColliderC.h"
#include "Mesh.h"
#include "ModelLibrary.h"
#include "Entity.h"
#include "TransformationC.h"

#include "ShaderHeaven.h"
#include "commonShader.h"

namespace pp
{
	commonShader* MeshColliderC::shader = nullptr;

	MeshColliderC::MeshColliderC(void) :
		ColliderC(MESH_TYPE),
		meshName("none"),
		modelMatrix(nullptr)
	{
		if (shader == nullptr)
			shader = ShaderHeaven::getInstance()->commonshader;
	}


	MeshColliderC::~MeshColliderC(void)
	{
	}

	void MeshColliderC::update(const float& dt)
	{
		if (updatedFlag)
		{
			

			// check for valid mesh or not
			map<string, Mesh*>::iterator it = ModelLibrary::getInstance()->models.find(meshName);

			if (it == ModelLibrary::getInstance()->models.end())
			{
				printf("invalid mesh pls \n");
				throw 0;
			}

			// update the mesh 
			mesh = ModelLibrary::getInstance()->models[meshName];

			// get the tris
			tris = mesh->allTris;

			// get the handle for model matrix
			modelMatrix = &getOwner()->transformC->getFinalMat4();

			updatedFlag = false;
		}

		bool &haschange = getOwner()->transformC->hasChange;
		if (haschange)
		{
			// update the hit box
			mat4f &m = *modelMatrix;

			if (tris.size() > 0)
			{
				auto it2 = tris.begin();
				for (auto it = mesh->allTris.begin(); it != mesh->allTris.end(); it += 3)
				{
					*(it2) = (m * ((*(it))));
					*(it2 + 1) = (m * ((*(it + 1))));
					*(it2 + 2) = (m * ((*(it + 2))));

					it2 += 3;
				}

				haschange = false;
			}

			
		}
		
	}

	void MeshColliderC::draw(void) const
	{
		if (getOwner()->isActive())
		{
			if (modelMatrix)
			{
				shader->load_ModelMatrix(*modelMatrix);
				mesh->Render();
			}
		}
	}

	void MeshColliderC::save(ofstream& myFile, const unsigned int & guid)
	{

	}
}
