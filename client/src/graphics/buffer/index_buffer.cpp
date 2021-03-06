#include "index_buffer.h"

nario::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_bufferId);
}

void nario::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
}

void nario::IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

nario::IndexBuffer::IndexBuffer(GLuint * data, GLsizei count)
	:_count(count)
{
	glGenBuffers(1, &_bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind 使得调用bind后生效
}

nario::IndexBuffer::IndexBuffer(GLushort* data, GLuint count)
	:_count(count)
{
	glGenBuffers(1, &_bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind 使得调用bind后生效
}

