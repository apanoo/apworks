#include "tile_layer.h"
#include "batch_renderer2d.h"

nario::TileLayer::TileLayer(Shader* shader)
	:Layer(new BatchRenderer2d(), shader, Matrix4().orthographicMatrix(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

nario::TileLayer::~TileLayer()
{

}

