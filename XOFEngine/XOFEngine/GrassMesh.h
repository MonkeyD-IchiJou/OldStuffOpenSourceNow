#ifndef GRASS_MESH_H
#define GRASS_MESH_H

#include "Mesh.h"

namespace pp
{
	class GrassMesh : public Mesh
	{
	public:
		GrassMesh(void);
		virtual ~GrassMesh(void);

		// load the mesh
		bool LoadMesh(void) override;

		void Render(void) override;
		void RenderWithoutBind(void) override;
	};
}

#endif


