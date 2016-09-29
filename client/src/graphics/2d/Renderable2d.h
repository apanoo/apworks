#pragma once
#include "graphics/buffer/Buffer.h"
#include "graphics/buffer/IndexBuffer.h"
#include "graphics/buffer/VertexArray.h"
#include "graphics/Shader.h"

#include "math/Maths.h"

namespace nario {

	struct VertexData
	{
		Vector3 vertices;
		Vector4 color;
	};

	class Renderable2d
	{
	public:
		explicit Renderable2d(const Vector3& position, const Vector2& size, const Vector4& color, Shader& shader);
		virtual ~Renderable2d();

	public:
		inline const Vector3& getPosition() const { return _position; }
		inline const Vector2& getSize() const { return _size; }
		inline const Vector4& getColor() const { return _color; }

		inline const VertexArray* getVAO() const { return _vertexArray; }
		inline const IndexBuffer* getIBO() const { return _indexBuffer; }

		inline Shader& getShader() const { return _shader; }
	protected:
		Vector3 _position;
		Vector2 _size;
		Vector4 _color;

		VertexArray* _vertexArray;
		Buffer* _vertexBuffer;
		Buffer* _colorBuffer;
		IndexBuffer* _indexBuffer;

		Shader& _shader;
	};
}