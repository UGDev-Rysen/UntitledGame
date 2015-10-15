#pragma once

#include <vector>
#include <graphics/font.h>
#include <utils/unicitydef.h>
namespace u_engine { namespace graphics {

	class FontManager {

	private:
		static std::vector<Font*> m_Fonts;
	public:
		static UE_void add(Font* font);
		static Font* get();
		static Font* get(const UE_string& name);
		static Font* get(const UE_string& name, UE_uint size);
		static UE_void clean();
	private:
		FontManager() { }
	};

} }