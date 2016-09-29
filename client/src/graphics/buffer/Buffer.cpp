#include "Buffer.h"

nario::Buffer::~Buffer()
{
	glDeleteBuffers(1, &_bufferId);
}

void nario::Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
}

void nario::Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

nario::Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
	: _componentCount(componentCount)
{
	glGenBuffers(1, &_bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind 使得调用bind之后才生效
}

