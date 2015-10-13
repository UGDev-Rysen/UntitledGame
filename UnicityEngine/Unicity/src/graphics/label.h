#pragma once

#include <graphics/renderable2d.h>
#include <graphics/font_manager.h>
#include <utils/unicitydef.h>
#include <u_engine_includes.h>
namespace u_engine { namespace graphics {

	class Label : public Renderable2D {

	public:

		Font* m_Font;
		UE_string text;
		maths::vec3& position;
		UE_float x, y;

	public:
		Label(const UE_string& text, UE_float x, UE_float y, UE_uint color);
		Label(const UE_string& text, UE_float x, UE_float y, Font* font, UE_uint color);
		Label(const UE_string& text, UE_float x, UE_float y, const UE_string& font, UE_uint color);
		Label(const UE_string& text, UE_float x, UE_float y, const UE_string& font, UE_uint size, UE_uint color);
		UE_void submit(Renderer2D* renderer) const override;
		UE_void validateFont(const UE_string& name, UE_int size = -1);

	};


} }