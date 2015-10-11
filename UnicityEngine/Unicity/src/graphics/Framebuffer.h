#pragma once

#include <u_engine_includes.h>

#include <maths/vec4.h>
#include <maths/tvec2.h>
#include <graphics/texture.h>

namespace u_engine { namespace graphics {

	class Framebuffer
	{
	private:
		struct FramebufferData
		{
			GLuint framebufferID;
			GLuint depthbufferID;
		};

		Texture* m_Texture;
		FramebufferData m_Data;
		maths::tvec2<UE_uint> m_Size;
		UE_uint& m_Width;
		UE_uint& m_Height;

		maths::vec4 m_ClearColor;
	public:
		Framebuffer(const maths::tvec2<UE_uint>& size);
		Framebuffer(UE_uint width, UE_uint height);
		~Framebuffer();

		UE_void Bind() const;
		UE_void Clear();

		inline const maths::tvec2<UE_uint>& GetSize() const { return m_Size; }
		inline const UE_uint GetWidth() const { return m_Width; }
		inline const UE_uint GetHeight() const { return m_Height; }
		inline const Texture* GetTexture() const { return m_Texture; }

		inline UE_void SetClearColor(const maths::vec4& color) { m_ClearColor = color; }
	private:
		UE_void Create(UE_uint width, UE_uint height);
	};

} }