#include "simplerenderer2D.h"



namespace u_engine { namespace graphics {

	void SimpleRenderer2D::submit(const Renderable2D* renderable) {

		m_RenderQueue.push_back((StaticSprite*) renderable);
	}
	void SimpleRenderer2D::flush() {

		while (!m_RenderQueue.empty()) {
			const StaticSprite* sprite = m_RenderQueue.front();
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();


			sprite->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(sprite->getPosition()));
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);



			sprite->getIBO()->unbind();
			sprite->getVAO()->unbind();

			m_RenderQueue.pop_front();
		}
	}


} }