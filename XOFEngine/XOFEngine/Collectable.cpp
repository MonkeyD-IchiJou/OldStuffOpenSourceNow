#include "Collectable.h"
#include "Entity.h"
#include "TransformationC.h"
#include "DebugMesh.h"
#include "ModelLibrary.h"
#include "debugShader.h"
#include "ShaderHeaven.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "Scene3D.h"

namespace pp
{
	DebugMesh *Collectable::collectableMesh = nullptr;
	debugShader* Collectable::shader = nullptr;

	Collectable::Collectable(void) : 
		collectables(nullptr), 
		transformation(nullptr),
		p(nullptr)
	{
		shader = ShaderHeaven::getInstance()->debugshader;
		collectableMesh = dynamic_cast<DebugMesh*>(ModelLibrary::getInstance()->models["DRAGONBALL"]);


		p = PlayerManager::getInstance();
	}

	Collectable::~Collectable(void)
	{
	}

	void Collectable::create(void)
	{
		destroy();

		collectables = new Entity[500];
		transformation = new TransformationC[500];

		for (int i = 0; i < 500; ++i)
		{
			collectables[i].setActive(false);
			collectables[i].transformC = &transformation[i];
			collectables[i].AddComponent(collectables[i].transformC);
		}
	}

	void Collectable::draw(void) const
	{
		// draw pls
		if (tmatrix.size() > 0)
		{
			shader->Start();
			shader->load_color(vec3f(2.0f, 1.0f, 0.25f));
			collectableMesh->RenderInstancedTriangle(tmatrix);
			shader->Stop();
		}
	}

	void Collectable::add(const vec3f & pos)
	{
		for (int i = 0; i < 500; ++i)
		{
			if (!collectables[i].isActive())
			{
				collectables[i].setActive(true);
				collectables[i].transformC->position = pos;
				break;
			}
		}
	}

	void Collectable::update(const float & dt)
	{
		for (int i = 0; i < 500; ++i)
		{
			TransformationC &t = transformation[i];

			if (t.getOwner()->isActive())
			{
				vec3f dir = p->player[p->PlayerControlState]->transformC->position - t.position;
				float lenght = dir.lengthSquared();
				if (lenght < 36.f)
				{
					if (lenght < 1.f)
					{
						t.position.Set(-500.f, -100.f, 500.f);
						t.getOwner()->setActive(false);
						SceneManager::getInstance()->activeScene->point += 25;
					}
					else
					{
						dir.normalize();
						t.Translate(dir * dt * 40.f);
					}
					
				}

				t.update(dt);

				tmatrix.push_back(t.getFinalMat4());
			}
		}
	}

	void Collectable::lateUpdate(const float & dt)
	{
		if (tmatrix.size() > 0)
			tmatrix.clear();
	}

	void Collectable::destroy(void)
	{
		if (collectables != nullptr)
		{
			collectables->pureDestroy();
			delete[]collectables;
			collectables = nullptr;
		}

		if (transformation != nullptr)
		{
			delete[]transformation;
			transformation = nullptr;
		}

	}
}