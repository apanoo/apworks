#pragma once
#include "utils/StdAfx.h"

namespace nario {
	class Buffer
	{
	public:
		explicit Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~Buffer();

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return _componentCount; }

	private:
		GLuint _bufferId;
		GLuint _componentCount; // 分组,几个点一组
	};
}