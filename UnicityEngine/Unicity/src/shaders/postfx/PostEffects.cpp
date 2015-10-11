#include <shaders/postfx/PostEffects.h>

namespace u_engine { namespace graphics {

	PostEffects::PostEffects() { }
	PostEffects::~PostEffects() { }

	UE_void PostEffects::push(PostEffectsPass* pass) {

		m_Passes.push_back(pass);
	}

	UE_void PostEffects::pop() {

		m_Passes.pop_back();
	}

	UE_void PostEffects::RenderPostEffects(Framebuffer* source, Framebuffer* target, UE_uint quad, IndexBuffer* indices) {

		target->Bind();
		GLCall(glActiveTexture(GL_TEXTURE0));
		source->GetTexture()->bind();

		GLCall(glBindVertexArray(quad));
		indices->bind();

		for (PostEffectsPass* pass : m_Passes)
			pass->RenderPass(target);

		indices->unbind();
		GLCall(glBindVertexArray(0));

	}



} }