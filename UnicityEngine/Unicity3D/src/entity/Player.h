#pragma once

#include "Entity.h"

#include <graphics/Window.h>

class Player : public Entity
{
private:
	u_engine::maths::vec3 rotation;
    float mouse_sensitivity;
    float dy;
    const float JUMP_HEIGHT;
    bool jumping;
    bool light;
    float speed;
    VertexArray* target;
	u_engine::graphics::Window& m_Window;
	bool m_Wireframe;
public:
	Player(const u_engine::maths::vec3& spawn);
    void update();
    void render();
};