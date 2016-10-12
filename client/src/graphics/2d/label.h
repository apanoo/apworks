#pragma once
#include "graphics/2d/Renderable2d.h"
#include "graphics/2d/Renderer2d.h"
#include "math/maths.h"
#include <string>

namespace nario {
	class Label : public Renderable2d
	{
	public:
		Label(std::string text, float x, float y, unsigned int color, Font* font);
		~Label();

		void submit(Renderer2d* renderer) const override;
		inline std::string const getText() const { return _text; }
		inline void setText(const std::string& text) { _text = text; }
	private:
		std::string _text;
		Font* _font;
	};
}