#include "tile_layer.h"

TileLayer::TileLayer(nario::Shader* shader)
	:Layer(new nario::BatchRenderer2d(), shader, nario::Matrix4().orthographicMatrix(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

TileLayer::~TileLayer()
{

}

