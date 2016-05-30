#include "ShaderProgram.h"

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace pp
{
	GLint ShaderProgram::Result = GL_FALSE;
	int ShaderProgram::InfoLoglength = 0;

	ShaderProgram::ShaderProgram()
	{
		ProgramID = VertexShaderID = FragmentShaderID = GeometryShaderID = NULL;
	}

	ShaderProgram::ShaderProgram(const char * vertex_file_path, const char * fragment_file_path, char * geometry_file_path)
	{
		VertexShaderID = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
		if (geometry_file_path != nullptr)
		{
			GeometryShaderID = LoadShader(geometry_file_path, GL_GEOMETRY_SHADER);
		}
		FragmentShaderID = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

		

		// Link the program
		printf("Linking program\n");
		ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		if (geometry_file_path != nullptr)
		{
			glAttachShader(ProgramID, GeometryShaderID);
		}
		glAttachShader(ProgramID, FragmentShaderID);

		

		glLinkProgram(ProgramID);


		// validate the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLoglength);

		if (InfoLoglength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLoglength + 1);
			glGetProgramInfoLog(ProgramID, InfoLoglength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}

		// delete shader
		CleanUp();
	}

	GLuint ShaderProgram::LoadShader(const char * file_path, GLenum type)
	{
		// Create the shaders
		GLuint ShaderID = glCreateShader(type);

		// Read the Vertex Shader code from the file
		std::string ShaderCode;
		std::ifstream ShaderStream(file_path, std::ios::in);

		if (ShaderStream.is_open()) {
			std::string Line = "";
			while (getline(ShaderStream, Line))
				ShaderCode += "\n" + Line;
			ShaderStream.close();
		}
		else {
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
			return 0;
		}

		// Compile Shader
		printf("Compiling shader : %s\n", file_path);
		char const * ShaderSourcePointer = ShaderCode.c_str();
		glShaderSource(ShaderID, 1, &ShaderSourcePointer, NULL);
		glCompileShader(ShaderID);

		// Check Shader
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLoglength);
		if (InfoLoglength > 0) {
			std::vector<char> ShaderErrorMessage(InfoLoglength + 1);
			glGetShaderInfoLog(ShaderID, InfoLoglength, NULL, &ShaderErrorMessage[0]);
			printf("%s\n", &ShaderErrorMessage[0]);
		}

		return ShaderID;
	}

	void ShaderProgram::Start(void)
	{
		glUseProgram(ProgramID);
	}

	void ShaderProgram::Stop(void)
	{
		glUseProgram(0);
	}

	void ShaderProgram::CleanUp(void)
	{
		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);
		glDetachShader(ProgramID, GeometryShaderID);
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
		glDeleteShader(GeometryShaderID);
	}

	unsigned int ShaderProgram::getUniformLocation(const char* uniformName)
	{
		return glGetUniformLocation(ProgramID, uniformName);
	}

	unsigned int ShaderProgram::getUniformBlockIndex(const char * blockName)
	{
		return glGetUniformBlockIndex(ProgramID, blockName);
	}

	void ShaderProgram::UniformBlockBinding(const char * blockName, const int& index)
	{
		// First. We get the relevant block indices
		GLuint uniformBlock = getUniformBlockIndex(blockName);

		// Then we link each shader's uniform block to this uniform binding point
		glUniformBlockBinding(ProgramID, uniformBlock, index);
	}

	void ShaderProgram::loadU_1f(const unsigned int& location, const float& value) const
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::loadU_Vec3f(const unsigned int& location, const vec3f& vector3f) const
	{
		glUniform3fv(location, 1, &vector3f.x);
	}

	void ShaderProgram::loadU_Vec4f(const unsigned int & location, const vec4f & vec4f) const
	{
		glUniform4fv(location, 1, &vec4f.x);
	}

	void ShaderProgram::loadU_1i(const unsigned int& location, const int& value) const
	{
		glUniform1i(location, value);
	}

	void ShaderProgram::loadU_Bool(const unsigned int& location, const bool& value) const
	{
		int toLoad = 0;

		if (value)
		{
			toLoad = 1;
		}

		glUniform1i(location, value);
	}

	void ShaderProgram::loadU_Mat4f(const unsigned int& location, const mat4f& matrix, bool transpose) const
	{
		glUniformMatrix4fv(location, 1, transpose, &matrix.a[0]);
	}

	void ShaderProgram::loadU_Vec2f(const unsigned int& location, const float& x, const float& y) const
	{
		float arr[2];
		arr[0] = x;
		arr[1] = y;

		glUniform2fv(location, 1, arr);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(ProgramID);
	}
}
