#pragma once

#include "Block.h"

class AirBlock : public Block
{
public:
    AirBlock(unsigned short ID);
	void render(const u_engine::maths::vec3& position);
};