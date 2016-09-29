#include "Renderable2d.h"

nario::Renderable2d::Renderable2d(const Vector3& position, const Vector2& size, const Vector4& color, Shader& shader)
	:_position(position), _size(size), _color(color), _shader(shader)
{
	_vertexArray = new VertexArray();

	GLfloat vertices[] = {
		0,			 0,			  0,
		0,			 size.getY(), 0,
		size.getX(), size.getY(), 0,
		size.getX(), 0,			  0
	};

	GLfloat colors[] = {
		color.getX(), color.getY(), color.getZ(), color.getW(),
		color.getX(), color.getY(), color.getZ(), color.getW(),
		color.getX(), color.getY(), color.getZ(), color.getW(),
		color.getX(), color.getY(), color.getZ(), color.getW()
	};

	_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

	GLushort indices[] = {
		0, 1, 2, 2, 3, 0
	};
	_indexBuffer = new IndexBuffer(indices, 6);
}

nario::Renderable2d::~Renderable2d()
{
	delete _vertexArray;
	delete _indexBuffer;
}


