#include "renderable2d.h"
#include "renderer2d.h"

nario::Renderable2d::Renderable2d(const Vector3& position, const Vector2& size, unsigned int color)
	:_position(position), _size(size), _color(color), _texture(nullptr)
{
	setUVdefault();
}

nario::Renderable2d::Renderable2d()
	:_texture(nullptr)
{
	setUVdefault();
}

nario::Renderable2d::~Renderable2d()
{

}

void nario::Renderable2d::submit(Renderer2d* renderer) const
{
	renderer->submit(this);
}

void nario::Renderable2d::setUVdefault()
{
	_uv.push_back(Vector2(0, 0));
	_uv.push_back(Vector2(0, 1));
	_uv.push_back(Vector2(1, 1));
	_uv.push_back(Vector2(1, 0));
}

