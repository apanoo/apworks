#include "GLSLProgram.h"

namespace nario {
	GLSLProgram::GLSLProgram()
		: _programId(0), _vertexShaderId(0), _fragmentShaderId(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{

	}

	void GLSLProgram::linkShaders()
	{

	}
}