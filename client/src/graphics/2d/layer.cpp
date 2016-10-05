#include "layer.h"

nario::Layer::~Layer()
{
	delete _shader;
	delete _renderer;
	for (unsigned int i = 0; i < _renderables.size(); ++i)
	{
		delete _renderables[i];
	}
}

void nario::Layer::add(Renderable2d* renderable)
{
	_renderables.push_back(renderable);
}

void nario::Layer::render()
{
	_shader->enable();
	_renderer->begin();
	for (const Renderable2d* renderable : _renderables)
	{
		renderable->submit(_renderer);
	}
	_renderer->end();
	_renderer->flush();
	_shader->disable();
}

nario::Layer::Layer(Renderer2d* renderer, Shader* shader, const Matrix4& projection)
	:_projection(projection), _renderer(renderer), _shader(shader)
{
	_shader->enable();
	_shader->setUniformMat4("pr_matrix", _projection);
	_shader->disable();
}
