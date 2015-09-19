#pragma once

#include <deque>
#include "renderer2D.h"
#include "static_sprite.h"


namespace u_engine { namespace graphics {

	class SimpleRenderer2D : public Renderer2D {

	private:
		std::deque<const StaticSprite*> m_RenderQueue;

	public:
			

		void submit(const Renderable2D* renderable) override;
		void flush() override;



	};

	
} }