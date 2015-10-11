#pragma once

#include "../graphics/VertexArray.h"

#include <shaders/Shader.h>

class Level;

class Entity
{
protected:
	VertexArray *model;
	u_engine::graphics::Shader *shader;
	u_engine::maths::vec3 position;
	Level *level;
public:
	Entity();
	virtual ~Entity();
	void init(Level *level);
	u_engine::maths::vec3 get_position();
	virtual void update() = 0;
	virtual void render() = 0;
};
