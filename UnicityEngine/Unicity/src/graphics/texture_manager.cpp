#include <graphics/texture_manager.h>

namespace u_engine { namespace graphics {

	std::vector<Texture*> TextureManager::m_Textures;

	UE_void TextureManager::add(Texture* texture)
	{
		m_Textures.push_back(texture);
	}

	Texture* TextureManager::get(const UE_string& name)
	{
		for (Texture* texture : m_Textures)
		{
			if (texture->getName() == name)
				return texture;
		}
		return nullptr;
	}

	UE_void TextureManager::clean()
	{
		for (UE_uint i = 0; i < m_Textures.size(); i++)
			delete m_Textures[i];
	}

} }