#pragma once

#include <shaders/Shader.h>

class Shaders
{
public:
	static u_engine::graphics::Shader* BLOCK;
	static u_engine::graphics::Shader* HUD;
public:
	static void Init();
};