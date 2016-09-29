#pragma once
#include "utils/StdAfx.h"
#include <vector>
#include "Buffer.h"

namespace nario {
	class VertexArray
	{
	public:
		explicit VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	private:
		GLuint _arrayId;
		std::vector<Buffer*> _buffers;
	};
}