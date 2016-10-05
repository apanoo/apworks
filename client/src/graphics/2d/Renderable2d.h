#pragma once
#include "graphics/buffer/buffer.h"
#include "graphics/buffer/index_buffer.h"
#include "graphics/buffer/vertex_array.h"
#include "graphics/shader.h"

#include "math/Maths.h"

namespace nario {

	struct VertexData
	{
		Vector3 vertex;
		//Vector4 color;
		unsigned int color;
	};

	class Renderer2d;
	class Renderable2d
	{
	protected:
		Renderable2d() {}
	public:
		explicit Renderable2d(const Vector3& position, const Vector2& size, const Vector4& color);
		virtual ~Renderable2d();
		virtual void submit(Renderer2d* renderer) const;
	public:
		inline const Vector3& getPosition() const { return _position; }
		inline const Vector2& getSize() const { return _size; }
		inline const Vector4& getColor() const { return _color; }
	protected:
		Vector3 _position;
		Vector2 _size;
		Vector4 _color;
	};
}