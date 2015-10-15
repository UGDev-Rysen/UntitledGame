#include <graphics/texture.h>

namespace u_engine { namespace graphics {

	TextureWrap Texture::s_WrapMode = TextureWrap::REPEAT;
	TextureFilter Texture::s_FilterMode = TextureFilter::LINEAR;

	Texture::Texture(UE_uint width, UE_uint height, UE_uint bits)
		: m_Width(width), m_Height(height), m_FileName("NULL"), m_Bits(24) {

		m_TID = load();
	}

	Texture::Texture(const UE_string& name, const UE_string& filename)
		: m_Name(name), m_FileName(filename)
	{
		m_TID = load();
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_TID));
	}

	GLuint Texture::load()
	{
		BYTE* pixels = nullptr;
		if (m_FileName != "NULL")
			pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height, &m_Bits);
		else
			m_Bits = 32; //Temporary

		GLuint result;

		GLCall(glGenTextures(1, &result));
		GLCall(glBindTexture(GL_TEXTURE_2D, result));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)s_FilterMode));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)s_FilterMode));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s_WrapMode));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)s_WrapMode));



		if (m_Bits != 24 && m_Bits != 32)
			UNICITY_ERROR("[Texture] Unsupported image bit-depth! (", m_Bits, ")");

		GLint internalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
		GLenum format = m_Bits == 32 ?

		GL_BGRA : GL_BGR;

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		delete[] pixels;

		return result;
	}

	UE_void Texture::bind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TID));
	}

	UE_void Texture::unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

} }