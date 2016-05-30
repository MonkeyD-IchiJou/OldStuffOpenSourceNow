#ifndef LINERENDERERC_H
#define LINERENDERERC_H

#include "RendererC.h"
#include <string>

#include "MathsHeader.h"
using std::string;

namespace pp
{
	class Mesh;
	class commonShader;
	class LineMesh;

	class LineRendererC : public RendererC
	{
	public:
		LineRendererC(void);
		virtual ~LineRendererC(void);

		void update(const float& dt) override;
		void draw(void) const override;
		void save(ofstream& myFile, const unsigned int & guid) override;

	public:
		inline void setPos(const vec3f & v) { this->pos = v; updatedFlag = true; }
		inline void setTar(const vec3f & v) { this->tar = v; updatedFlag = true; }

		LineMesh* linemesh;

	private:
		static commonShader* shader;

		vec3f pos, tar;
	};
}

#endif
