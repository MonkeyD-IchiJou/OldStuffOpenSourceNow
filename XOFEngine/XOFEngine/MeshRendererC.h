#ifndef MESHRENDERERC_H
#define MESHRENDERERC_H

#include "RendererC.h"
#include <string>

#include "MathsHeader.h"
using std::string;

namespace pp
{
	class Mesh;
	class GeometryPassShader;
	class depthShader;
	class CameraC;

	class MeshRendererC : public RendererC
	{
	public:
		MeshRendererC(void);
		virtual ~MeshRendererC(void);

		void update(const float& dt) override;
		void draw(void) const override;
		void drawDepth(void) const;
		void save(ofstream& myFile, const unsigned int & guid) override;

	public:
		// store the meshname only
		string meshName;

		// for rendering
		Mesh* mesh;

	private:
		static GeometryPassShader* shader;
		static depthShader* depthshader;

		vec3f* pos;
	};
}

#endif
