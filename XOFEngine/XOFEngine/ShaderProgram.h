#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

//Include GLEW
#include "GLH.h"

#include "mat4.h"
#include "vec4.h"
using namespace Math;

namespace pp
{
	class ShaderProgram
	{
	public:
		ShaderProgram();        // constructor
		ShaderProgram(const char * vertex_file_path, const char * fragment_file_path, char * geometry_file_path = nullptr);
		~ShaderProgram();

		void Start(void);       // start shader
		void Stop(void);        // stop shader
		void CleanUp(void);     // delete shader to save memory space after link program


	protected:
		unsigned int getUniformLocation(const char* uniformName);
		unsigned int getUniformBlockIndex(const char* blockName);
		void UniformBlockBinding(const char* blockName, const int& index);
		virtual void getAllUniformLocations(void) = 0;

		void loadU_1f(const unsigned int& location, const float& value) const;  // glUniform1f
		void loadU_Vec3f(const unsigned int& location, const vec3f& vector3f) const; // glUniform3f
		void loadU_Vec4f(const unsigned int& location, const vec4f& vec4f) const; // glUniform3f
		void loadU_1i(const unsigned int& location, const int& value) const;    // glUniform1i
		void loadU_Bool(const unsigned int& location, const bool& value) const;
		void loadU_Mat4f(const unsigned int& location, const mat4f& matrix, bool transpose = false) const;  //glUniformMatrix4fv
		void loadU_Vec2f(const unsigned int& location, const float& x, const float& y) const;

	private:
		unsigned int ProgramID, VertexShaderID, FragmentShaderID, GeometryShaderID;
		static GLuint LoadShader(const char * file_path, GLenum type);

		static int Result;
		static int InfoLoglength;    // variable used to validate program
	};
}


#endif