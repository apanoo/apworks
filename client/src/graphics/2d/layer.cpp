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
}

nario::Layer::Layer(Renderer2d* renderer, Shader* shader, const Matrix4& projection)
	:_projection(projection), _renderer(renderer), _shader(shader)
{
	_shader->enable();
	_shader->setUniformMat4("pr_matrix", _projection);
	int texIds[] = {
		0,   1,  2,  3,  4,  5,  6,  7,  8,  9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
		30, 31
	};
	shader->setUniform1iv("textures", texIds, 32);
	_shader->disable();
}
