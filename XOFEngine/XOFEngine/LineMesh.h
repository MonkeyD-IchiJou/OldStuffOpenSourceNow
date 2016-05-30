#ifndef LINEDRAW_MESH_H
#define LINEDRAW_MESH_H

#include "Mesh.h"

namespace pp
{
	class LineMesh : public Mesh
	{
	public:
		LineMesh(void);
		virtual ~LineMesh(void);

		// load the mesh
		bool LoadMesh(void) override;

		void Render(void) override;
		void RenderWithoutBind(void) override;

		void updatePosAndTar(const vec3f& pos, const vec3f& tar);
		vec3f pos, tar;
	};
}

#endif


