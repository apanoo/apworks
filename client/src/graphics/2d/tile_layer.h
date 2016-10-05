#pragma once
#include "layer.h"

namespace nario {
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();

	};
}