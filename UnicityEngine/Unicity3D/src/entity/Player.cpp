#include "Player.h"
#include "../level/Level.h"

#include "../Game.h"

#include <maths/maths.h>
#include "../Shaders.h"

using namespace u_engine;
using namespace maths;
using namespace graphics;

Player::Player(const vec3& position)
	: m_Window(*Game::WindowHandle), m_Wireframe(false),
	mouse_sensitivity(0.2f), dy(0.0f), JUMP_HEIGHT(1.5f), jumping(false), light(true), speed(0.7f)
{
	this->position = position;
	this->position.y = -this->position.y;
	shader = Shaders::BLOCK;

	const GLfloat TSIZE = 0.2f;
	GLfloat vertices[4 * 3] = {
		-TSIZE / 2.0f, -TSIZE / 2.0f, 0.0f,
		-TSIZE / 2.0f, TSIZE / 2.0f, 0.0f,
		TSIZE / 2.0f, TSIZE / 2.0f, 0.0f,
		TSIZE / 2.0f, -TSIZE / 2.0f, 0.0f
	};
	GLuint indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	target = new VertexArray(vertices, indices, (GLfloat*)NULL, 4 * 3, 6);
	m_Window.setMouseCursor(UE_NO_CURSOR);
}

void Player::update()
{
	if (m_Window.isKeyPressed(VK_W))
	{
		float xa = -sin(toRadians(rotation.y)) * speed;
		float za = cos(toRadians(rotation.y)) * speed;
		vec3 pos = vec3(position.x, position.y + 8.0f, position.z);
		vec3 rot = vec3(xa, 0.0f, za);
		//        if (level->raycast_block_id(position, rot, 32.0f) < 2 && level->raycast_block_id(pos, rot, 32.0f) < 2) {
		position.x += xa;
		position.z += za;
		//        }
	}
	if (m_Window.isKeyPressed(VK_S))
	{
		float xa = sin(toRadians(rotation.y)) * speed;
		float za = -cos(toRadians(rotation.y)) * speed;
		//  if (level->raycast_collision(position, vec3(xa, za, 0.0f)) < 2) {
		position.x += xa;
		position.z += za;
		//  }
	}
	if (m_Window.isKeyPressed(VK_A))
	{
		float xa = -sin(toRadians(rotation.y - 90.0f)) * speed;
		float za = cos(toRadians(rotation.y - 90.0f)) * speed;
		//  if (level->raycast_collision(position, vec3(xa, za, 0.0f)) < 2) {
		position.x += xa;
		position.z += za;
		//   }
	}
	if (m_Window.isKeyPressed(VK_D))
	{
		float xa = -sin(toRadians(rotation.y + 90.0f)) * speed;
		float za = cos(toRadians(rotation.y + 90.0f)) * speed;
		// if (level->raycast_collision(position, vec3(xa, za, 0.0f)) < 2) {
		position.x += xa;
		position.z += za;
		//  }
	}
	vec3 gravity = vec3(0, -1, 0);
	bool block = level->raycast_block_id(position, gravity, 10.0f) > 1;
	if (!block || jumping)
		position.y -= dy;
	if (dy < -1.0f)
		dy = -1.0f;

	if (dy > 2.0f) dy = 2.0f;

	//    if (position.y > -48.0f) position.y = -48.0f;
	if (jumping)
		dy += 0.5f;
	if (dy > JUMP_HEIGHT)
		jumping = false;
	if (!jumping && dy > -JUMP_HEIGHT)
		dy -= 0.15f;

	if (m_Window.isKeyPressed(VK_SPACE) && !jumping && block)
		jumping = true;
	if (m_Window.isKeyTyped(VK_F))
		light = !light;
	// TODO: Sparky engine mouse grabbing
	if (m_Window.isMouseGrabbed())
	{
		vec2 mouse = m_Window.getMousePosition();
		mouse.x = 960 / 2 - mouse.x;
		mouse.y = 540 / 2 - mouse.y;
		rotation.x -= mouse.y * mouse_sensitivity;
		rotation.y -= mouse.x * mouse_sensitivity;
		m_Window.setMousePosition(vec2(960 / 2, 540 / 2));
	}
	if (m_Window.isKeyPressed(VK_ESCAPE))
	{
		m_Window.setMouseGrabbed(false);
		m_Window.setMouseCursor(1);
	}
	if (rotation.x < -90.0f) rotation.x = -90.0f;
	if (rotation.x > 90.0f) rotation.x = 90.0f;

	vec3 b = level->raycast_block(position, rotation);
	level->select_block(b);
	if (m_Window.isMouseButtonClicked(SP_MOUSE_LEFT))
	{
		if (!m_Window.isMouseGrabbed())
		{
			m_Window.setMouseGrabbed(true);
			m_Window.setMouseCursor(UE_NO_CURSOR);
		}
		else
		{
			unsigned short& rid = level->pick_block(position, rotation);
			if (rid != Level::NULL_BLOCK) rid = 1;
		}
	}
	else if (m_Window.isMouseButtonPressed(SP_MOUSE_RIGHT))
	{
		// Place block!
		unsigned short& bid = level->raycast_pre_block_id(position, rotation);
		if (bid == 1) bid = 2;
	}
	if (m_Window.isKeyTyped(VK_Q))
	{
		m_Wireframe = !m_Wireframe;
		if (m_Wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Player::render()
{
	shader->bind();
	mat4 vw_matrix = mat4::rotation(rotation.x, vec3(1.0f, 0.0f, 0.0f));
	vw_matrix *= mat4::rotation(rotation.y, vec3(0.0f, 1.0f, 0.0f));
	vw_matrix *= mat4::translation(position);
	shader->setUniformMat4("vw_matrix", vw_matrix);
	shader->setUniform3f("player_pos", vec3(-position.x, -position.y, -position.z));

	if (light)
		shader->setUniform1f("light_on", 1);
	else
		shader->setUniform1f("light_on", 0);

	shader->unbind();
	Shaders::HUD->bind();
	target->render();
	Shaders::HUD->unbind();
}

