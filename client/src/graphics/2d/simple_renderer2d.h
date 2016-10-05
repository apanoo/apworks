#pragma once
#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"

namespace nario {
	class SimpleRenderer2d : public Renderer2d
	{
	public:
		void submit(const Renderable2d* renderable) override;
		void flush() override;

	private:
		std::deque<const StaticSprite*> _renderQueue;
	};
}