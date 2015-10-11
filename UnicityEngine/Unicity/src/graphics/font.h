#pragma once

#include <string>
#include <freetype-gl\freetype-gl.h>
#include <maths/vec2.h>
#include <u_engine_includes.h>
namespace u_engine { namespace graphics {

	class Font {

	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		UE_float m_Size;

		maths::vec2 m_Scale;
		UE_string m_Name;
		UE_string m_FileName;

	public:

		Font(UE_string name, UE_string filename, UE_float size);
		Font(UE_string name, const byte* data, UE_uint datasize, UE_float size);


		UE_void setScale(UE_float x, UE_float y);

		inline const UE_uint getID() const { return m_FTAtlas->id; }
		inline const maths::vec2& getScale() const { return m_Scale; }
		inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
		inline const UE_string& getName() const { return m_Name; }
		inline const UE_string& getFileName() const { return m_FileName; }
		inline const UE_float getSize() const { return m_Size; }


	};

} }