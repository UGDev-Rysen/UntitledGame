#include <audio/SoundManager.h>

namespace u_engine { namespace audio {

		gau_Manager*	SoundManager::m_Manager		= nullptr;
		ga_Mixer*		SoundManager::m_Mixer		= nullptr;

		std::vector<Sound*> SoundManager::m_Sounds;

		UE_void SoundManager::init()
		{
			gc_initialize(0);
			m_Manager	= gau_manager_create();
			m_Mixer		= gau_manager_mixer(m_Manager);
		}

		Sound* SoundManager::add(Sound* sound)
		{
			m_Sounds.push_back(sound);

			return sound;
		}

		Sound* SoundManager::get(const UE_string& name)
		{
			for (Sound* sound : m_Sounds)
			{
				if (sound->getName() == name)
					return sound;
			}
			return nullptr;
		}

		UE_void SoundManager::clean()
		{
			for (UE_int i = 0; i < m_Sounds.size(); i++)
				delete			m_Sounds[i];

			gau_manager_destroy(m_Manager);
			gc_shutdown();
		}

		UE_void SoundManager::update()
		{
			gau_manager_update(m_Manager);
		}

} }