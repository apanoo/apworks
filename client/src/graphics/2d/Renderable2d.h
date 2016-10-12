#pragma once
#include "graphics/buffer/buffer.h"
#include "graphics/buffer/index_buffer.h"
#include "graphics/buffer/vertex_array.h"
#include "graphics/shader.h"
#include <vector>

#include "math/Maths.h"
#include "graphics/texture.h"

namespace nario {

	struct VertexData
	{
		Vector3 vertex;
		Vector2 uv;
		float tid; // texture id
		unsigned int color;
	};

	class Renderer2d;
	class Renderable2d
	{
	protected:
		Renderable2d();
	public:
		explicit Renderable2d(const Vector3& position, const Vector2& size, const Vector4& color);
		virtual ~Renderable2d();
		virtual void submit(Renderer2d* renderer) const;
	public:
		inline const Vector3& getPosition() const { return _position; }
		inline void setPosition(const Vector3& position) { _position = position; }

		inline const Vector2& getSize() const { return _size; }
		inline void setSize(const Vector2& size) { _size = size; }

		inline const Vector4& getColor() const { return _color; }
		inline void setColor(const Vector4& color) { _color = color; }

		inline const std::vector<Vector2>& getUVs() const { return _uv; }

		// texture id
		inline const GLuint getTid() const { return _texture == nullptr ? 0 : _texture->getId(); }
	private:
		void setUVdefault();
	protected:
		Vector3 _position;
		Vector2 _size;
		Vector4 _color;
		std::vector<Vector2> _uv;
		Texture* _texture;
	};
}