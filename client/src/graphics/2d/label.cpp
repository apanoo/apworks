#include "label.h"

nario::Label::~Label()
{

}

void nario::Label::submit(Renderer2d* renderer) const
{
	renderer->drawString(_text, _position, _color, *_font);
}

nario::Label::Label(std::string text, float x, float y, unsigned int color, Font* font)
	:Renderable2d(), _text(text), _font(font)
{
	_color = color;
	_position = Vector3(x, y, 0);
}

