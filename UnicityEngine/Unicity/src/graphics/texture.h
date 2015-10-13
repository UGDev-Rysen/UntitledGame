#pragma once
#include <u_engine_includes.h>
#include <iostream>
#include <string>



namespace u_engine { namespace graphics{

	enum class TextureWrap {

		REPEAT						= GL_REPEAT,
		CLAMP						= GL_CLAMP,
		MIRRORED_REPEAT				= GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE				= GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER				= GL_CLAMP_TO_BORDER
	};

	enum class TextureFilter {

		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST
	};

	class Texture
	{
	private:
		static TextureWrap s_WrapMode;
		static TextureFilter s_FilterMode;
	private:
		UE_string m_Name, m_FileName;
		UE_uint m_TID;
		UE_uint m_Width, m_Height;
		UE_uint m_Bits;
	public:
		Texture(UE_uint width, UE_uint height, UE_uint bits = 24);
		Texture(const UE_string& name, const UE_string& filename);
		~Texture();
		UE_void bind() const;
		UE_void unbind() const;
		
		inline const UE_string& getName() const { return m_Name; }
		inline const UE_uint getID() const { return m_TID; }
		inline const UE_uint getWidth() const { return m_Width; }
		inline const UE_uint getHeight() const { return m_Height; }
	public:
		inline static UE_void SetWrap(TextureWrap mode) { s_WrapMode = mode; }
		inline static UE_void setFilter(TextureFilter mode) { s_FilterMode = mode; }
	private:
		GLuint load();
	};

} }