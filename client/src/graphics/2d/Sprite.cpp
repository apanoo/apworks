#include "sprite.h"

nario::Sprite::~Sprite()
{

}

nario::Sprite::Sprite(float x, float y, float width, float height, const Vector4& color)
	:Renderable2d(Vector3(x, y, 0), Vector2(width, height), color)
{

}

