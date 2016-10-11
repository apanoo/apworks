#pragma once
#include <cstddef>
#include <vector>
#include "renderer2d.h"
#include "graphics/buffer/index_buffer.h"
#include "extension/freetype-gl/freetype-gl.h"

namespace nario {

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)								// 每个顶点包含的字节数
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4						// sprite对应4个顶点
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

	class BatchRenderer2d : public Renderer2d
	{
	public:
		BatchRenderer2d();
		~BatchRenderer2d();

		void begin() override;
		void submit(const Renderable2d* renderable) override;
		void drawString(const std::string& text, const Vector3& position, const Vector4& color) override;
		void end() override;

		void flush() override;
	private:
		void init();
	private:
		GLuint _VAO;
		GLuint _VBO;
		IndexBuffer* _IBO;
		GLsizei _indexCount;

		VertexData* _buffer;

		std::vector<GLuint> _textureSlots; // for multi texture render

		ftgl::texture_atlas_t* _FTAtlas;
		ftgl::texture_font_t* _FTFont;
	};
}