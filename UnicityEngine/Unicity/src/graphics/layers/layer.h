#pragma once

#include "../renderer2D.h"
#include "../renderable2D.h"

namespace u_engine { namespace graphics {

	class Layer {

	protected:

		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		maths::mat4 m_ProjectionMatrix;


	public:

		Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
		virtual ~Layer();
		virtual void add(Renderable2D* renderable); // TODO: Return Renderable2D*
		virtual void render();

		inline const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; }
	};


} }