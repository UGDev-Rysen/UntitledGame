#pragma once

#include <cstddef>
#include <u_engine_includes.h>
#include <graphics/renderer2D.h>
#include <graphics/renderable2D.h>
#include <graphics/buffers/indexbuffer.h>
#include <graphics/Framebuffer.h>


namespace u_engine { namespace graphics {


	

	class BatchRenderer2D : public Renderer2D {
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		VertexData* m_Buffer;

		std::vector<GLuint> m_TextureSlots;

		Framebuffer* m_FrameBuffer;
		Framebuffer* m_PostEffectsBuffer;
		UE_int m_ScreenBuffer;
		maths::tvec2<UE_uint> m_ViewportSize, m_ScreenSize;
		Shader* m_SimpleShader;
		UE_uint m_ScreenQuad;
	public:
		BatchRenderer2D(const maths::tvec2<UE_uint>& screenSize);

		~BatchRenderer2D();
		UE_void begin() override;
		UE_void submit(const Renderable2D* renderable) override;
		UE_void drawString(const UE_string& text, const maths::vec3& position, const Font& font, UE_uint color) override;
		UE_void end() override;
		UE_void flush() override;

		inline UE_void SetScreenSize(const maths::tvec2<UE_uint>& size) { m_ScreenSize = size; }
		inline const maths::tvec2<UE_uint>& GetScreenSize() const { return m_ScreenSize; }
		inline UE_void SetViewportSize(const maths::tvec2<UE_uint>& size) { m_ViewportSize = size; }
		inline const maths::tvec2<UE_uint>& GetViewportSize() const { return m_ViewportSize; }
		

	private:
		UE_void init();
		UE_float submitTexture(UE_uint textureID);
		UE_float submitTexture(const Texture* texture);


	};



} }