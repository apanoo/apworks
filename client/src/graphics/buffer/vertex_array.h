#pragma once
#include "utils/stdafx.h"
#include <vector>
#include "buffer.h"

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