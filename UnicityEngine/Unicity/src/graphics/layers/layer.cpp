#include <graphics/layers/layer.h>

namespace u_engine { namespace graphics {

	Layer::Layer(	Renderer2D*			renderer, 
					Shader*				shader, 
					maths::mat4			projectionMatrix)
		:			renderer2D(			renderer), 
					m_Shader(			shader), 
					m_ProjectionMatrix(	projectionMatrix) {

		m_Shader->bind();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);

		GLint texIDs[] = {
		
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		m_Shader->setUniform1iv("textures", texIDs, 32);
		m_Shader->unbind();
	}

	Layer::~Layer() {

		delete m_Shader;
		delete renderer2D;

		for (UE_uint i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	Renderable2D* Layer::add(Renderable2D* renderable) {
		m_Renderables.push_back(renderable);
		return renderable;
	}

	UE_void Layer::render() {
	
		m_Shader->bind();

		renderer2D->begin();
		for (const Renderable2D* renderable : m_Renderables)
			renderable->submit(renderer2D);
		renderer2D->end();

		renderer2D->flush();

	}




} }