#include "BatchRenderer2d.h"

nario::BatchRenderer2d::~BatchRenderer2d()
{
	delete _IBO;
	glDeleteBuffers(1, &_VBO);
}

// bind vbo and map buffer
void nario::BatchRenderer2d::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void nario::BatchRenderer2d::submit(Renderable2d* renderable)
{
	const Vector3& position = renderable->getPosition();
	const Vector2& size = renderable->getSize();
	const Vector4& color = renderable->getColor();

	_buffer->vertex = position;
	_buffer->color = color;
	_buffer++;

	_buffer->vertex = Vector3(position.getX(), position.getY() + size.getY(), position.getZ());
	_buffer->color = color;
	_buffer++;

	_buffer->vertex = Vector3(position.getX() + size.getX(), position.getY() + size.getY(), position.getZ());
	_buffer->color = color;
	_buffer++;

	_buffer->vertex = Vector3(position.getX() + size.getX(), position.getY(), position.getZ());
	_buffer->color = color;
	_buffer++;

	_indexCount += 6;
}

// unbind vbo and unmap buffer
void nario::BatchRenderer2d::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void nario::BatchRenderer2d::flush()
{
	glBindVertexArray(_VAO);
	_IBO->bind();

	glDrawElements(GL_TRIANGLES, _indexCount, /*GL_UNSIGNED_SHORT*/GL_UNSIGNED_INT, NULL);

	_IBO->unbind();
	glBindVertexArray(0);

	_indexCount = 0;
}

void nario::BatchRenderer2d::init()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO); 

	glBindVertexArray(_VAO);			 // bind vao
	glBindBuffer(GL_ARRAY_BUFFER, _VBO); // bind buffer

	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind buffer

	/*GLushort*/GLuint* indeices = new GLuint[RENDERER_INDICES_SIZE]; // indices array
	int offset = 0;
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indeices[i] = offset + 0;
		indeices[i + 1] = offset + 1;
		indeices[i + 2] = offset + 2;
		indeices[i + 3] = offset + 2;
		indeices[i + 4] = offset + 3;
		indeices[i + 5] = offset + 0;

		offset += 4;
	}

	_IBO = new IndexBuffer(indeices, RENDERER_INDICES_SIZE);

	glBindVertexArray(0); // unbind vao
}

nario::BatchRenderer2d::BatchRenderer2d()
	:_indexCount(0)
{
	init();
}

