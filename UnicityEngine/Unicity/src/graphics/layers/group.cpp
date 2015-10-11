#include <graphics/layers/group.h>


namespace u_engine { namespace graphics {

	Group::Group(const maths::mat4&		transform)
		: m_TransformationMatrix(		transform) 
	{
	}

	Group::~Group() {

		for (UE_uint i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];

	}


	UE_void Group::add(Renderable2D*	renderable) {
		m_Renderables.push_back(	renderable);
	}

	UE_void Group::submit(Renderer2D* renderer) const {
		renderer->push(m_TransformationMatrix);

		for (const Renderable2D* renderable : m_Renderables)
			renderable->submit(renderer);

		renderer->pop();
	}


} }
