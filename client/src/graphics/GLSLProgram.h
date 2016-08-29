#pragma once
#include <string>
#include <GL/glew.h>

namespace nario {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void linkShaders();
	private:
		GLuint _programId;
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;
	};
}
