#include "Shaders.h"

#include <maths/maths.h>

u_engine::graphics::Shader* Shaders::BLOCK = nullptr;
u_engine::graphics::Shader* Shaders::HUD = nullptr;

void Shaders::Init()
{
	using namespace u_engine::maths;

	mat4 pr_matrix = u_engine::maths::mat4::perspective(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	BLOCK = new u_engine::graphics::Shader("res/shaders/shader.vert", "res/shaders/shader.frag");
	BLOCK->bind();
	BLOCK->setUniformMat4("pr_matrix", pr_matrix);
	BLOCK->setUniformMat4("vw_matrix", u_engine::maths::mat4::translation(vec3(0.0f, 0.0f, -500.0f)));
	BLOCK->setUniform1f("tex_id", 0);
	BLOCK->unbind();

	mat4 ortho = mat4::orthographic(-16.0f * 2.0f, 16.0f * 2.0f, 9.0f * 2.0f, -9.0f * 2.0f, -1.0f, 1.0f);
	HUD = new u_engine::graphics::Shader("res/shaders/hud.vert", "res/shaders/hud.frag");
	HUD->bind();
	HUD->setUniformMat4("pr_matrix", ortho);
	HUD->unbind();
}