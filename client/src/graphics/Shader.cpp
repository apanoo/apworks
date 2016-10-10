#include "shader.h"
#include "utils/file_utils.h"
#include "log/aplog.h"
#include <vector>

nario::Shader::Shader(const char* vertPath, const char* fragPath)
	:_vertPath(vertPath), _fragPath(fragPath)
{
	_shaderId = load();
}

nario::Shader::~Shader()
{
	glDeleteProgram(_shaderId);
}

/**
* enable the shader
*/
void nario::Shader::enable() const
{
	glUseProgram(_shaderId);
}

/**
* disable the shader
*/
void nario::Shader::disable() const
{
	glUseProgram(0);
}

void nario::Shader::setUniform1f(const GLchar* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void nario::Shader::setUniform1fv(const GLchar* name, float* value, int count)
{
	glUniform1fv(getUniformLocation(name), count, value);
}

void nario::Shader::setUniform1i(const GLchar* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void nario::Shader::setUniform1iv(const GLchar* name, int* value, int count)
{
	glUniform1iv(getUniformLocation(name), count, value);
}

void nario::Shader::setUniform2f(const GLchar* name, Vector2& vector)
{
	glUniform2f(getUniformLocation(name), vector.getX(), vector.getY());
}

void nario::Shader::setUniform3f(const GLchar* name, const Vector3& vector)
{
	glUniform3f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
}

void nario::Shader::setUniform4f(const GLchar* name, const Vector4& vector)
{
	glUniform4f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ(), vector.getW());
}

void nario::Shader::setUniformMat4(const GLchar* name, const Matrix4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

/**
* load shader
*/
GLuint nario::Shader::load()
{
	GLuint program = glCreateProgram();

	// create shader
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// read shader file
	std::string vertTm = FileUtils::readFile(_vertPath);
	std::string fragTm = FileUtils::readFile(_fragPath);
	const char* vertSource = vertTm.c_str();
	const char* fragmentSource = fragTm.c_str();
	
	// bind shader source
	glShaderSource(vertex, 1, &vertSource, NULL);
	
	// compile shader
	glCompileShader(vertex);

	// get compile result
	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		// get compile errors
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		aplog::logerr("Error to compile vert shader!", &error[0]);
		glDeleteShader(vertex);
		return 0;
	}

	// same as vert
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		// get compile errors
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		aplog::logerr("Error to compile frag shader!", &error[0]);
		glDeleteShader(fragment);
		return 0;
	}

	// attach shader
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	// link program
	glLinkProgram(program);

	// validate program
	glValidateProgram(program);

	// delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return program;
}

GLuint nario::Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(_shaderId, name);
}

