#pragma once

#include <graphics/layers/layer.h>
#include <graphics/BatchRenderer2D.h>
#include <maths/maths.h>

class TileLayer : public u_engine::graphics::Layer
{
public:
	TileLayer(u_engine::graphics::Shader* shader);
	~TileLayer();
};