#pragma once
#include <cstddef>
#include "renderer2d.h"
#include "graphics/buffer/index_buffer.h"

namespace nario {

#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)								// 每个顶点包含的字节数
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4						// sprite对应4个顶点
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_COLOR_INDEX 2

	class BatchRenderer2d : public Renderer2d
	{
	public:
		BatchRenderer2d();
		~BatchRenderer2d();

		void begin() override;
		void submit(const Renderable2d* renderable) override;
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
	};
}