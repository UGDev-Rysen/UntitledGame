#include "texture.h"

#include <graphics/Texture.h>

Texture* Texture::dirt = (Texture*)NULL;
Texture* Texture::stone = (Texture*)NULL;

Texture::Texture(const std::string& file)
{
	texture = load(file);
}

void Texture::LOAD()
{
	// Load static textures here
	glActiveTexture(GL_TEXTURE0);
	dirt = new Texture("res/dirt.png");
	stone = new Texture("res/stone.png");
}

void Texture::DESTROY()
{
	delete dirt;
	delete stone;
}

GLuint Texture::load(const std::string& filepath)
{
	u_engine::graphics::Texture::setFilter(u_engine::graphics::TextureFilter::NEAREST);
	u_engine::graphics::Texture* texture = new u_engine::graphics::Texture(filepath, filepath);
	return texture->getID();
}

void Texture::enable()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::disable()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}