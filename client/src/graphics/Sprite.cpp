#include "Sprite.h"

namespace nario {

	Sprite::Sprite()
		: _vboId(0), _x(0), _y(0), _width(1), _height(1)
	{

	}

	Sprite::~Sprite()
	{
		// Delete buffer
		if (_vboId != 0)
		{
			glDeleteBuffers(1, &_vboId);
		}
	}

	void Sprite::init(float x, float y, float width, float height)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		if (_vboId == 0)
		{
			glGenBuffers(1, &_vboId);
		}

		float vertexData[12];
		// First triangle
		vertexData[0] = x + width;
		vertexData[1] = y + width;

		vertexData[2] = x;
		vertexData[3] = y + height;

		vertexData[4] = x;
		vertexData[5] = y;

		// Second triangle
		vertexData[6] = x;
		vertexData[7] = y;

		vertexData[8] = x + width;
		vertexData[9] = y;

		vertexData[10] = x + width;
		vertexData[11] = y + height;

		// Bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboId);

		// Upload buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		// Unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		// Bind
		glBindBuffer(GL_ARRAY_BUFFER, _vboId);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);

		// Unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}