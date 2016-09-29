#pragma once
#include "Renderer2d.h"
#include "graphics/buffer/VertexArray.h"

namespace nario {

#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

	class BatchRenderer2d : public Renderer2d
	{
	public:
		BatchRenderer2d();
		~BatchRenderer2d();

		void submit(Renderable2d* renderable) override;
		void flush() override;
	private:
		void init();
	private:
		VertexArray _VAO;
		IndexBuffer* _IBO;
		GLsizei _indexCount;
		GLuint _VBO;
	};
}