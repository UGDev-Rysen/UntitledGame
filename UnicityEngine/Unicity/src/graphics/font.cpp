#include <graphics/font.h>

namespace u_engine { namespace graphics {

	Font::Font(UE_string name, UE_string filename, UE_float size)
		: m_Name(name), m_FileName(filename), m_Size(size), m_Scale(maths::vec2(1, 1)) {

		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());
		UNICITY_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");
	}


	Font::Font(UE_string name, const byte* data, UE_uint datasize, UE_float size)
		: m_Name(name), m_FileName("NULL"), m_Size(size), m_Scale(maths::vec2(1, 1)) {

		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
		m_FTFont = ftgl::texture_font_new_from_memory(m_FTAtlas, size, data, datasize);
		UNICITY_ASSERT(m_FTFont, "Failed to load font from data!");
	}

	UE_void Font::setScale(UE_float x, UE_float y) {
		m_Scale = maths::vec2(x, y);
	}


} }