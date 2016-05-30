#ifndef VERTEX_H
#define VERTEX_H

#include "vec3.h"
using namespace Math;
#include "engine_common.h"

#define NUM_BONES_PER_VEREX 4

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }

	void Set(float u, float v) { this->u = u; this->v = v; }

	TexCoord operator-(const TexCoord& rhs) 
	{ 
		return TexCoord(this->u - rhs.u, this->v - rhs.v); 
	} //Vector subtraction
};

struct Vertex
{
	vec3f pos;
	vec3f normal;
	TexCoord texCoord;
	vec3f tangent;

	Vertex(void)
	{
	};
};

struct VertexGrass
{
	vec3f pos;
	vec3f normal;
	vec3f random;

	VertexGrass(void)
	{
	};
};


#endif