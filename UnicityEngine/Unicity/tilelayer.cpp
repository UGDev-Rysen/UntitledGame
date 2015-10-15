#include <../tilelayer.h>


TileLayer::TileLayer(u_engine::graphics::Shader* shader)
	: Layer(new u_engine::graphics::BatchRenderer2D(u_engine::maths::tvec2<UE_uint>(0,0)), shader, u_engine::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}

TileLayer::~TileLayer()
{
}