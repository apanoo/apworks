#include "StaticSprite.h"

nario::StaticSprite::~StaticSprite()
{
	delete _vertexArray;
	delete _indexBuffer;
}

nario::StaticSprite::StaticSprite(float x, float y, float width, float height, const Vector4& color, Shader& shader)
	:Renderable2d(Vector3(x, y, 0), Vector2(width, height), color), _shader(shader)
{
	_vertexArray = new VertexArray();

	GLfloat vertices[] = {
		0,			 0,			  0,
		0,			 height,      0,
		width,		 height,      0,
		width,		 0,			  0
	};

	GLfloat colors[] = {
		color.getX(), color.getY(), color.getZ(), color.getW(),
		color.getX(), color.getY(), color.getZ(), color.getW(),
		color.getX(), color.getY(), color.getZ(), color.getW(),
		color.getX(), color.getY(), color.getZ(), color.getW()
	};

	_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

	/*GLushort*/GLuint indices[] = {
		0, 1, 2, 2, 3, 0
	};
	_indexBuffer = new IndexBuffer(indices, 6);
}

