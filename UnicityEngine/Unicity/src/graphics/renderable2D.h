#pragma once
#include <u_engine_includes.h>
#include <graphics/buffers/buffers.h>
#include <maths/maths.h>
#include <shaders/shader.h>
#include <graphics/texture.h>
#include <graphics/renderer2D.h>
#include <utils/unicitydef.h>

namespace u_engine { namespace graphics {

	struct VertexData {

		maths::vec3 vertex;
		maths::vec2 uv;
		maths::vec2 mask_uv;
		UE_float tid;
		UE_float mid;
		UE_uint color;

	};
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)

	class Renderable2D {
	protected:
		maths::vec3 m_Position;
		maths::vec2 m_Size;
		UE_uint m_Color;
		std::vector<maths::vec2> m_UV;
		Texture* m_Texture;

	protected:
		Renderable2D() : m_Texture(nullptr){ setUVDefaults(); }



	public:

		Renderable2D(maths::vec3 position, maths::vec2 size, UE_uint color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr) {
			
			setUVDefaults();
		}

		virtual ~Renderable2D() { }

		virtual UE_void submit(Renderer2D* renderer) const {

			renderer->submit(this);
		}

		UE_void setColor(UE_uint color) { m_Color = color; }
		UE_void setColor(const maths::vec4& color) {

			UE_uint r = (UE_uint)(color.x * 255.0f);
			UE_uint g = (UE_uint)(color.y * 255.0f);
			UE_uint b = (UE_uint)(color.z * 255.0f);
			UE_uint a = (UE_uint)(color.w * 255.0f);
			
			m_Color = a << 24 | b << 16 | g << 8 | r;
		}



		inline const maths::vec3& getPosition() const { return m_Position; }
		inline const maths::vec2& getSize() const { return m_Size; }
		inline const UE_uint getColor() const { return m_Color; }
		inline const std::vector<maths::vec2>& getUV() const { return m_UV; }

		inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }
		inline const Texture* getTexture() const { return m_Texture; }


	private:

		UE_void setUVDefaults() {

			m_UV.push_back(maths::vec2(0, 0));
			m_UV.push_back(maths::vec2(0, 1));
			m_UV.push_back(maths::vec2(1, 1));
			m_UV.push_back(maths::vec2(1, 0));
		}


	};



} }