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

		inline const std::vector<Renderable2d*>& getRenderables() const { return _renderables; }

	public:
		Layer(Renderer2d* renderer, Shader* shader, const Matrix4& projection);
		Renderer2d* _renderer;
		std::vector<Renderable2d*> _renderables;
		Shader* _shader;
		Matrix4 _projection;
	};
}