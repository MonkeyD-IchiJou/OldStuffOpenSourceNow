#include "MatricesUBO.h"

namespace pp
{
	MatricesUBO::MatricesUBO(void)
	{
		create();
	}

	MatricesUBO::~MatricesUBO(void)
	{
	}

	void MatricesUBO::create(void)
	{
		clear();

		// Now actually create the buffer
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4f), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		// Define the range of the buffer that links to a uniform binding point
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(mat4f));
	}

	void MatricesUBO::updateALL(const mat4f & view, const mat4f & projection)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4f), &projection);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4f), sizeof(mat4f), &view);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void MatricesUBO::load_ViewMatrix(const mat4f & view)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4f), sizeof(mat4f), &view);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void MatricesUBO::load_ProjectionMatrix(const mat4f & projection)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4f), &projection);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}