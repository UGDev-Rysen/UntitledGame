#include <graphics/label.h>

namespace u_engine { namespace graphics {

	Label::Label(const UE_string& text, UE_float x, UE_float y, UE_uint color)
		: Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get("SourceSansPro")) {
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const UE_string& text, UE_float x, UE_float y, Font* font, UE_uint color)
	 : Renderable2D(), text(text), position(m_Position), m_Font(font) {

		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	Label::Label(const UE_string& text, UE_float x, UE_float y, const UE_string& font, UE_uint color)
		 : Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font)) {
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
		
		validateFont(font);
		}
	
	Label::Label(const UE_string& text, UE_float x, UE_float y, const UE_string& font, UE_uint size, UE_uint color)
		 : Renderable2D(), text(text), position(m_Position), m_Font(FontManager::get(font, size)) {
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
		
		validateFont(font, size);
		}


	UE_void Label::submit(Renderer2D* renderer) const {

		renderer->drawString(text, position, *m_Font, m_Color);
	}


	UE_void Label::validateFont(const UE_string& name, UE_int size)
		 {
		if (m_Font != nullptr)
			return;
		
		std::cout << "NULL FONT! Font=" << name;
		if (size > 0)
			std::cout << ", Size=" << size;
		std::cout << std::endl;
		
		m_Font = FontManager::get("SourceSansPro");
		}


} }