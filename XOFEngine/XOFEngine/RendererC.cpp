#include "RendererC.h"

namespace pp
{
	RendererC::RendererC(const RENDER_TYPE& type) : 
		Component(RENDERER), 
		spherecollider(nullptr), 
		enabled(true), 
		type(type), 
		modelMatrix(nullptr), 
		prevMVPMatrix(nullptr),
		emissive(0.f), 
		shininess(32.f), 
		isVisible(true),
		isVisibleDepth(true)
	{
	}

	RendererC::~RendererC(void)
	{
		modelMatrix = nullptr;
		prevMVPMatrix = nullptr;
		spherecollider = nullptr;
	}

	void RendererC::update(const float& dt)
	{
		// here dun have
	}

	void RendererC::save(ofstream & myFile, const unsigned int & guid)
	{
	}
}
