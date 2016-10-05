#pragma once
#include "math/maths.h"
#include "renderable2d.h"
#include "graphics/buffer/vertex_array.h"
#include "graphics/buffer/index_buffer.h"
#include "graphics/shader.h"

namespace nario {
	class StaticSprite : public Renderable2d
	{
	public:
		StaticSprite(float x, float y, float width, float height, const Vector4& color, Shader& shader);
		~StaticSprite();

		inline const VertexArray* getVAO() const { return _vertexArray; }
		inline const IndexBuffer* getIBO() const { return _indexBuffer; }

		inline Shader& getShader() const { return _shader; }

	private:
		VertexArray* _vertexArray;
		IndexBuffer* _indexBuffer;

		Shader& _shader;
	};
}