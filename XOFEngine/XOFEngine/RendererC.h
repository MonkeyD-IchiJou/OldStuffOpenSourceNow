#ifndef RENDERERC_H
#define RENDERERC_H

#include "Component.h"
#include "MathsHeader.h"

namespace pp
{
	class Material;
	class SphereColliderC;

	enum RENDER_TYPE
	{
		MESH = 0,
		PARTICLE,
		LINE,
		LAST
	};

	class RendererC : public Component
	{
	public:
		RendererC(const RENDER_TYPE& type);
		virtual ~RendererC(void);

		virtual void update(const float& dt) override;
		virtual void draw(void) const = 0;
		virtual void save(ofstream& myFile, const unsigned int & guid) override;

	public:
		// variables

		// every renderer must have its own frustum sphere radius
		SphereColliderC* spherecollider;

		// Makes the rendered 3D object visible if enabled.
		bool enabled;

		// Is this renderer visible in any camera? 
		bool isVisible, isVisibleDepth;

		// type of rendering
		RENDER_TYPE type;

		// color
		vec3f color;
		float emissive;
		float shininess;

		// for motion blur
		mat4f* modelMatrix;
		mat4f* prevMVPMatrix;
	};

}

#endif

