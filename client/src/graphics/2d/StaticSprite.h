#pragma once
#include "math/Maths.h"
#include "Renderable2d.h"
#include "graphics/buffer/VertexArray.h"
#include "graphics/buffer/IndexBuffer.h"
#include "graphics/Shader.h"

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