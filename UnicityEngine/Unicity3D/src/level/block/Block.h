#pragma once

#include "../../graphics/VertexArray.h"
#include "../../graphics/Texture.h"
#include <maths/maths.h>
#include <shaders/Shader.h>

class Block
{
public:
    static Block *air, *dirt, *stone;
    const static float SIZE;
protected:
    unsigned short ID;
    static VertexArray* vao;
	u_engine::graphics::Shader* shader;
	u_engine::maths::vec3 color;
    Texture* texture;
public:
    Block(unsigned short ID);
    static void CREATE_ALL();
    static void DESTROY();
    virtual void update();
	virtual void render(const u_engine::maths::vec3& position);
private:
    void init();
};