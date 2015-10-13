#include "Entity.h"
#include "../level/Level.h"

Entity::Entity()
{
}

Entity::~Entity()
{
    delete model;
}

void Entity::init(Level *level)
{
    this->level = level;
}

u_engine::maths::vec3 Entity::get_position()
{
    return position;
}