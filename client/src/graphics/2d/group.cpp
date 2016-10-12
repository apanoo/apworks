#include "group.h"
#include "renderer2d.h"

nario::Group::Group(const Matrix4& transform)
	:_transformation(transform)
{

}

nario::Group::~Group()
{
	for (unsigned int i = 0; i < _renderables.size(); ++i)
	{
		delete _renderables[i];
	}
}

void nario::Group::submit(Renderer2d* renderer) const
{
	renderer->push(_transformation);
	for (const Renderable2d* renderable : _renderables)
	{
		renderable->submit(renderer);
	}
	renderer->pop();
}

void nario::Group::add(Renderable2d* renderable)
{
	_renderables.push_back(renderable);
}

