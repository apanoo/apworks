#include "sprite.h"

nario::Sprite::~Sprite()
{

}

nario::Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
	:Renderable2d(Vector3(x, y, 0), Vector2(width, height), color)
{

}

nario::Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
	:Renderable2d(Vector3(x, y, 0), Vector2(width, height), 0xffffffff)
{
	_texture = texture;
}

