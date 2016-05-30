#ifndef AXIS_MESH_H
#define AXIS_MESH_H

#include "Mesh.h"

namespace pp
{
	class AxisLineMesh : public Mesh
	{
	public:
		AxisLineMesh(void);
		virtual ~AxisLineMesh(void);

		// load the mesh
		bool LoadMesh() override;

		void Render(void) override;
		void RenderWithoutBind(void) override;
	};
}

#endif


