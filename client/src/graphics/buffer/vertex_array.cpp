#include "vertex_array.h"

nario::VertexArray::~VertexArray()
{
	// delete all buffers
	for (unsigned int i = 0; i < _buffers.size(); i++)
	{
		delete _buffers[i];
	}
	glDeleteVertexArrays(1, &_arrayId);
}

void nario::VertexArray::addBuffer(Buffer* buffer, GLuint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->unbind();
	unbind();
}

void nario::VertexArray::bind() const
{
	glBindVertexArray(_arrayId);
}

void nario::VertexArray::unbind() const
{
	glBindVertexArray(0);
}

nario::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_arrayId);
}

