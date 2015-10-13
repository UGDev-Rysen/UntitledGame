#pragma once

#include <vector>

#include <graphics/Framebuffer.h>
#include <graphics/buffers/indexbuffer.h>
#include <shaders/postfx/PostEffectsPass.h>


namespace u_engine { namespace graphics {

	//The postfx pipeline ;)

	class PostEffects {

	private:
		std::vector<PostEffectsPass*> m_Passes;
	public:

		PostEffects();
		~PostEffects();
		UE_void push(PostEffectsPass* pass);
		UE_void pop();

		UE_void RenderPostEffects(Framebuffer* source, Framebuffer* target, UE_uint quad, IndexBuffer* indices);
	};

} }