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
		explicit Renderable2d(const Vector3& position, const Vector2& size, unsigned int color);
		virtual ~Renderable2d();
		virtual void submit(Renderer2d* renderer) const;
	public:
		inline const Vector3& getPosition() const { return _position; }
		inline void setPosition(const Vector3& position) { _position = position; }

		inline const float getPositionX() { return _position.getX(); }
		inline void setPositionX(float x) { _position = Vector3(x, _position.getY(), _position.getZ()); }

		inline const float getPositionY() { return _position.getY(); }
		inline void setPositionY(float y) { _position = Vector3(_position.getX(), y, _position.getZ()); }

		inline const float getPositionZ() { return _position.getZ(); }
		inline void setPositionZ(float z) { _position = Vector3(_position.getX(), _position.getY(), z); }

		inline const Vector2& getSize() const { return _size; }
		inline void setSize(const Vector2& size) { _size = size; }

		inline const unsigned int getColor() const { return _color; }
		inline void setColor(unsigned int color) { _color = color; }
		inline void setColor(const Vector4& color)
		{
			int r = (int)(color.getX() * 255.0f);
			int g = (int)(color.getY() * 255.0f);
			int b = (int)(color.getZ() * 255.0f);
			int a = (int)(color.getW() * 255.0f);

			_color = a << 24 | b << 16 | g << 8 | r;
		}

		inline const std::vector<Vector2>& getUVs() const { return _uv; }

		// texture id
		inline const GLuint getTid() const { return _texture == nullptr ? 0 : _texture->getId(); }
	private:
		void setUVdefault();
	protected:
		Vector3 _position;
		Vector2 _size;
		unsigned int _color; // 0xffffffff 32位从低位到高位每8位一组分别表示RGBA
		std::vector<Vector2> _uv;
		Texture* _texture;
	};
}