#pragma once
#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"

namespace nario {
	class SimpleRenderer2d : public Renderer2d
	{
	public:
		void submit(Renderable2d* renderable) override;
		void flush() override;

	private:
		std::deque<StaticSprite*> _renderQueue;
	};
}