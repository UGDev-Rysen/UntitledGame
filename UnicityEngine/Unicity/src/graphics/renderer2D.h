#pragma once

#include <vector>
#include <glew.h>
#include <maths/maths.h>
#include <graphics/font.h>
#include <utils/unicitydef.h>
#include <graphics/texture.h>
#include <graphics/Mask.h>
#include <shaders/postfx/PostEffects.h>

namespace u_engine { namespace graphics {

	class Renderable2D;

	enum class RenderTarget {

		SCREEN = 0,
		BUFFER = 1
	};

	class Renderer2D {

	protected:

		std::vector<maths::mat4> m_TransformationStack;
		const maths::mat4* m_TransformationBack;
		const Mask* m_Mask;
		RenderTarget m_Target;
		PostEffects* m_PostEffects;
		UE_bool m_PostEffectsEnabled;

	protected:
		Renderer2D()
		: m_Mask(nullptr), m_PostEffectsEnabled(true) {

			m_TransformationStack.push_back(maths::mat4::identity());
			m_TransformationBack = &m_TransformationStack.back();
			m_Target = RenderTarget::SCREEN;
		}

	public:

		virtual ~Renderer2D() { }
		UE_void push(const maths::mat4& matrix, UE_bool override = false) {

			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

			m_TransformationBack = &m_TransformationStack.back();
		}


		UE_void pop() {

			//TODO: Add to log!
			if (m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();

			m_TransformationBack = &m_TransformationStack.back();


		}

		inline UE_void SetRenderTarget(RenderTarget target) { m_Target = target; }
		inline const RenderTarget GetRenderTarget() const { return m_Target; }
		
		inline UE_void SetPostEffects(bool enabled) { m_PostEffectsEnabled = enabled; }
		inline UE_bool GetPostEffects() const { return m_PostEffectsEnabled; }
		inline UE_void AddPostEffectsPass(PostEffectsPass* pass) { m_PostEffects->push(pass); }


		virtual UE_void begin() { };
		virtual UE_void setMask(const Mask* mask) { m_Mask = mask; }
		virtual UE_void submit(const Renderable2D* renderable) = 0;
		virtual UE_void drawString(const UE_string& text, const maths::vec3& position, const Font& font, UE_uint color) { }
		virtual UE_void end() { }
		virtual UE_void flush() = 0;



	};


} }