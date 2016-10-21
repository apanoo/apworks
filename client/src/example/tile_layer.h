#pragma once
#include "graphics/2d/layer.h"
#include "graphics/2d/batch_renderer2d.h"

class TileLayer : public nario::Layer
{
public:
	TileLayer(nario::Shader* shader);
	~TileLayer();

};