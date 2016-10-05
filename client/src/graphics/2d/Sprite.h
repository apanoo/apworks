#pragma once
#include "renderable2d.h"

namespace nario {
	class Sprite : public Renderable2d
	{
	public:
		Sprite(float x, float y, float width, float height, const Vector4& color);
		~Sprite();

	private:

	};
}