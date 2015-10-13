#pragma once

#include <graphics/renderable2D.h>
#include <u_engine_includes.h>
namespace u_engine { namespace graphics {

	class Group : public Renderable2D {

	private:

		std::vector<Renderable2D*>	m_Renderables;
		maths::mat4					m_TransformationMatrix;

	public:

		~Group();
		Group(const maths::mat4&	transform);
		UE_void add(Renderable2D*		renderable);
		UE_void submit(Renderer2D*		renderer) const override;

		maths::mat4& getTransformRef() { return m_TransformationMatrix; }
	};


} }
