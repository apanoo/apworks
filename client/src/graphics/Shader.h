#pragma once
#include "utils/stdafx.h"
#include "math/maths.h"

namespace nario {
	class Shader
	{
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		void disable() const;

		/**
		* Set uniform for shader
		*/
		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, Vector2& vector);
		void setUniform3f(const GLchar* name, const Vector3& vector);
		void setUniform4f(const GLchar* name, const Vector4& vector);
		void setUniformMat4(const GLchar* name, const Matrix4& matrix);

	private:
		GLuint load();
		GLuint getUniformLocation(const GLchar* name);

	private:
		GLuint _shaderId;
		const char* _vertPath;
		const char* _fragPath;
	};
}