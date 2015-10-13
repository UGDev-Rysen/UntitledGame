#pragma once

#include <vector>
#include <graphics/texture.h>

namespace u_engine { namespace graphics {

	class TextureManager
	{
	private:
		static std::vector<Texture*> m_Textures;
	public:
		static UE_void add(Texture* texture);
		static Texture* get(const UE_string& name);
		static UE_void clean();
	private:
		TextureManager() { }
	};

} }