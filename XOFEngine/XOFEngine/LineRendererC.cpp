#include "LineRendererC.h"
#include "ModelLibrary.h"

#include "Mesh.h"

#include "ShaderHeaven.h"
#include "commonShader.h"

#include "Entity.h"

#include "LineMesh.h"

namespace pp
{
	commonShader* LineRendererC::shader = nullptr;

	LineRendererC::LineRendererC(void) :
		RendererC(LINE),
		linemesh(nullptr)
	{
		if (shader == nullptr)
		{
			shader = ShaderHeaven::getInstance()->commonshader;
		}

		tar.Set(0, 0.f, 0.f);
		linemesh = new LineMesh();
		linemesh->LoadMesh();
	}

	LineRendererC::~LineRendererC(void)
	{
		shader = nullptr;

		if (linemesh != nullptr)
		{
			delete linemesh;
			linemesh = nullptr;
		}
	}

	void LineRendererC::update(const float& dt)
	{
		if (getOwner()->isActive() && this->updatedFlag)
		{
			linemesh->updatePosAndTar(pos, tar);

			updatedFlag = false;
		}
	}

	void LineRendererC::draw(void) const
	{
		if (getOwner()->isActive())
		{
			linemesh->Render();
		}
	}

	void LineRendererC::save(ofstream & myFile, const unsigned int & guid)
	{
		
	}


}
