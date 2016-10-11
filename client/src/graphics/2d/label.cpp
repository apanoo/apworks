#include "label.h"

nario::Label::~Label()
{

}

void nario::Label::submit(Renderer2d* renderer) const
{
	renderer->drawString(_text, _position, _color);
}

nario::Label::Label(std::string text, float x, float y, const Vector4& color)
	:Renderable2d(), _text(text)
{
	_color = color;
	_position = Vector3(x, y, 0);
}

