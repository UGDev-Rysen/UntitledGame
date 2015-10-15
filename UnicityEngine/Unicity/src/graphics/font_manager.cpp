#include <graphics/font_manager.h>

namespace u_engine { namespace graphics {

	std::vector<Font*> FontManager::m_Fonts;

	UE_void FontManager::add(Font* font) {

		m_Fonts.push_back(font);
	}

	Font* FontManager::get(const UE_string& name, UE_uint size) {

		for (Font* font : m_Fonts) {

			if (font->getSize() == size && font->getName() == name)
				return font;
		}
		//TODO: Maybe return a default font, to prevent errors/crahes?
		return nullptr;
	}

	Font* FontManager::get() {

		return m_Fonts[0];
	}


	Font* FontManager::get(const UE_string& name) {

		for (Font* font : m_Fonts) {

			if (font->getName() == name)
				return font;
		}
		//TODO: Maybe return a default font, to prevent errors/crahes?
		return nullptr;
	}


	UE_void FontManager::clean() {

		for (UE_int i = 0; i < m_Fonts.size(); i++)
			delete m_Fonts[i];
	}

} }