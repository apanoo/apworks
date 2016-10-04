#pragma once
#include "utils/StdAfx.h"

namespace nario {
	class IndexBuffer
	{
	public:
		explicit IndexBuffer(GLuint* data, GLsizei count);
		explicit IndexBuffer(GLushort* data, GLuint count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline GLuint getCount() const { return _count; }
	private:
		GLuint _bufferId;
		GLuint _count;
	};
}