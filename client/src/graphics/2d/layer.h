#pragma once
#include <vector>
#include "graphics/2d/renderer2d.h"
#include "graphics/2d/renderable2d.h"

namespace nario {
	class Layer
	{
	public:
		virtual ~Layer();
		virtual void add(Renderable2d* renderable);
		virtual void render();

	protected:
		Layer(Renderer2d* renderer, Shader* shader, const Matrix4& projection);
	protected:
		Renderer2d* _renderer;
		std::vector<Renderable2d*> _renderables;
		Shader* _shader;
		Matrix4 _projection;
	};
}