#pragma once


#include <graphics/Framebuffer.h>
#include <shaders/shader.h>

namespace u_engine { namespace graphics {

	class PostEffectsPass {

	private:
		Shader* m_Shader;
	public:
		PostEffectsPass(Shader* shader);
		~PostEffectsPass();

		UE_void RenderPass(Framebuffer* target);
	};

} }