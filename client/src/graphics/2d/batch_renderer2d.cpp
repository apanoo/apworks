#include "batch_renderer2d.h"

nario::BatchRenderer2d::~BatchRenderer2d()
{
	delete _IBO;
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}

// bind vbo and map buffer
void nario::BatchRenderer2d::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void nario::BatchRenderer2d::submit(const Renderable2d* renderable)
{
	const Vector3& position = renderable->getPosition();
	const Vector2& size = renderable->getSize();
	const unsigned int color = renderable->getColor();
	const std::vector<Vector2>& uv = renderable->getUVs();
	const GLuint tid = renderable->getTid(); // Texture id

	float ts = 0.0f;
	if (tid > 0) // with texture
	{
		bool found = false;
		for (unsigned int i = 0; i < _textureSlots.size(); ++i)
		{
			if (_textureSlots[i] == tid)
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}
		if (!found) 
		{
			if (_textureSlots.size() >= RENDERER_MAX_TEXTURES) // draw
			{
				end();
				flush();
				begin();
			}
			_textureSlots.push_back(tid);
			ts = (float)(_textureSlots.size());
		}
	}

	// point 1
	_buffer->vertex = *_transformationBack * position;
	_buffer->uv = uv[0];
	_buffer->tid = ts;
	_buffer->color = color;
	_buffer++;

	// point 2
	_buffer->vertex = *_transformationBack * Vector3(position.getX(), position.getY() + size.getY(), position.getZ());
	_buffer->uv = uv[1];
	_buffer->tid = ts;
	_buffer->color = color;
	_buffer++;

	// point 3
	_buffer->vertex = *_transformationBack * Vector3(position.getX() + size.getX(), position.getY() + size.getY(), position.getZ());
	_buffer->uv = uv[2];
	_buffer->tid = ts;
	_buffer->color = color;
	_buffer++;

	// point 4
	_buffer->vertex = *_transformationBack * Vector3(position.getX() + size.getX(), position.getY(), position.getZ());
	_buffer->uv = uv[3];
	_buffer->tid = ts;
	_buffer->color = color;
	_buffer++;

	_indexCount += 6;
}

void nario::BatchRenderer2d::drawString(const std::string& text, const Vector3& position, unsigned int color, const Font& font)
{
	using namespace ftgl; // freetype-gl

	float ts = 0.0f;
	bool found = false;
	for (unsigned int i = 0; i < _textureSlots.size(); ++i)
	{
		if (_textureSlots[i] == font.getId())
		{
			ts = (float)(i + 1);
			found = true;
			break;
		}
	}
	if (!found)
	{
		if (_textureSlots.size() >= 32) // draw
		{
			end();
			flush();
			begin();
		}
		_textureSlots.push_back(font.getId());
		ts = (float)(_textureSlots.size());
	}
	const Vector2& scale = font.getScale();

	float x = position.getX();
	for (unsigned int i = 0; i < text.length(); i++)
	{
		texture_font_t* ftFont = font.getFTFont();
		texture_glyph_t* glyph = texture_font_get_glyph(ftFont, text[i]);
		if (glyph != NULL)
		{
			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
				x += kerning / scale.getX();
			}

			float x0 = x + glyph->offset_x / scale.getX();
			float y0 = position.getY() + glyph->offset_y / scale.getY();
			float x1 = x0 + glyph->width / scale.getX();
			float y1 = y0 - glyph->height / scale.getY();

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			_buffer->vertex = *_transformationBack * Vector3(x0, y0, 0);
			_buffer->uv = Vector2(u0, v0);
			_buffer->tid = ts;
			_buffer->color = color;
			_buffer++;

			_buffer->vertex = *_transformationBack * Vector3(x0, y1, 0);
			_buffer->uv = Vector2(u0, v1);
			_buffer->tid = ts;
			_buffer->color = color;
			_buffer++;

			_buffer->vertex = *_transformationBack * Vector3(x1, y1, 0);
			_buffer->uv = Vector2(u1, v1);
			_buffer->tid = ts;
			_buffer->color = color;
			_buffer++;

			_buffer->vertex = *_transformationBack * Vector3(x1, y0, 0);
			_buffer->uv = Vector2(u1, v0);
			_buffer->tid = ts;
			_buffer->color = color;
			_buffer++;

			_indexCount += 6;

			x += (glyph->advance_x / scale.getX());
		}
	}
}

// unbind vbo and unmap buffer
void nario::BatchRenderer2d::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void nario::BatchRenderer2d::flush()
{
	for (unsigned int i = 0; i < _textureSlots.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textureSlots[i]);
	}

	glBindVertexArray(_VAO);
	_IBO->bind();

	glDrawElements(GL_TRIANGLES, _indexCount, /*GL_UNSIGNED_SHORT*/GL_UNSIGNED_INT, NULL);

	_IBO->unbind();
	glBindVertexArray(0);

	_indexCount = 0;
	_textureSlots.clear();
}

void nario::BatchRenderer2d::init()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO); 

	glBindVertexArray(_VAO);			 // bind vao
	glBindBuffer(GL_ARRAY_BUFFER, _VBO); // bind buffer

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_TID_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);

	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
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

