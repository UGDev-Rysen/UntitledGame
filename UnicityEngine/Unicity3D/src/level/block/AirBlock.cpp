#include "AirBlock.h"

AirBlock::AirBlock(unsigned short ID)
	: Block(ID)
{
	texture = Texture::dirt;
}

void AirBlock::render(const u_engine::maths::vec3& position)
{
}