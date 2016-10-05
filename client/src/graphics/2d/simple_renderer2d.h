#pragma once
#include <deque>
#include "Renderer2d.h"
#include "Static_Sprite.h"

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