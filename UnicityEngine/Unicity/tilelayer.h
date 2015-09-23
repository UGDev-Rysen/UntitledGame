#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/BatchRenderer2D.h"

class TileLayer : public u_engine::graphics::Layer
{
public:
	TileLayer(u_engine::graphics::Shader* shader);
	~TileLayer();
};