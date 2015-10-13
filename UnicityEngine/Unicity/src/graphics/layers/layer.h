#pragma once

#include <graphics/renderer2D.h>
#include <graphics/renderable2D.h>
#include <graphics/Mask.h>
#include <u_engine_includes.h>

namespace u_engine { namespace graphics {

	class Layer {

	public:
		Renderer2D* renderer2D;

	protected:

		std::vector<Renderable2D*>	m_Renderables;
		Shader*						m_Shader;
		maths::mat4					m_ProjectionMatrix;


	public:

		Layer(	Renderer2D*						renderer,
				Shader*							shader, 
				maths::mat4						projectionMatrix);
		virtual ~Layer();
		virtual Renderable2D* add(Renderable2D* renderable);
		inline UE_void setMask(const Mask* mask) const { renderer2D->setMask(mask); }
		virtual UE_void render();

		inline const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; }
	};


} }