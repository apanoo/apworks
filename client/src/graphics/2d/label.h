#pragma once
#include "graphics/2d/Renderable2d.h"
#include "graphics/2d/Renderer2d.h"
#include "math/maths.h"
#include <string>

namespace nario {
	class Label : public Renderable2d
	{
	public:
		Label(std::string text, float x, float y, const Vector4& color);
		~Label();

		void submit(Renderer2d* renderer) const override;
	private:
		std::string _text;
	};
}