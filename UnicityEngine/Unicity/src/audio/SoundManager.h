#pragma once

#include <vector>

#include <audio/sound.h>
#include <u_engine_includes.h>
#define GAU_THREAD_POLICY_MULTI 2

#include <gorilla-audio/ga.h>
#include <gorilla-audio/gau.h>

namespace u_engine { namespace audio {

		class SoundManager
		{
		private:
			friend class Sound;

			static gau_Manager*			m_Manager;
			static ga_Mixer*			m_Mixer;

			static std::vector<Sound*>	m_Sounds;
		public:
			static UE_void		init();
			static Sound*	add(Sound*				sound);
			static Sound*	get(const UE_string&	name);
			static UE_void		update();
			static UE_void		clean();
		private:
			SoundManager() { }
		};

} }