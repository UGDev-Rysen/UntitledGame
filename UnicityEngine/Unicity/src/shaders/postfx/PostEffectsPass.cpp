#include <shaders/postfx/PostEffectsPass.h>

namespace u_engine { namespace graphics {

	PostEffectsPass::PostEffectsPass(Shader* shader) 
	: m_Shader(shader) {

		m_Shader->bind();
		m_Shader->setUniform1i("tex", 0);
		m_Shader->unbind();
	}

	PostEffectsPass::~PostEffectsPass() { }

	UE_void PostEffectsPass::RenderPass(Framebuffer* target) {

		m_Shader->bind();
		m_Shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(0, target->GetWidth(), target->GetHeight(), 0, -1.0f, 1.0f));
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
		m_Shader->unbind();

	}
} }