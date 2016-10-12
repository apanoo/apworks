#pragma once
#include "renderable2d.h"
#include "graphics/texture.h"

namespace nario {
	class Sprite : public Renderable2d
	{
	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);
		~Sprite();

	private:

	};
}