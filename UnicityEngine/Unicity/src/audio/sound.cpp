#include <audio/sound.h>
#include <audio/SoundManager.h>

namespace u_engine {
	namespace audio {

		Sound::Sound(	const UE_string& name,
						const UE_string& filename)
			:	m_Name(		name),
				m_Filename(	filename), 
				m_Playing(	false), 
				m_Count(	0) {

			std::vector<UE_string> split = split_string(m_Filename, '.');
			if (split.size() < 2)
			{
				std::cout	<< "[Sound] Invalid file name '" 
							<< m_Filename << "'!" << std::endl;
				return;
			}
			m_Sound = gau_load_sound_file(	filename.c_str(), 
											split.back().c_str());

			if (m_Sound == nullptr)
				std::cout	<< "[Sound] Could not load file '" 
							<< m_Filename << "'!" << std::endl;
		}

		Sound::~Sound()
		{
			ga_sound_release(m_Sound);
		}

		UE_void Sound::play()
		{
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(	SoundManager::m_Mixer,
												m_Sound,
												&destroy_on_finish,
												&quit, NULL);
			m_Handle->sound		= this;
			ga_handle_play(		m_Handle);
			m_Playing			= true;
			m_Count++;
		}

		UE_void Sound::loop()
		{
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(	SoundManager::m_Mixer, 
												m_Sound, 
												&loop_on_finish, 
												&quit, NULL);
			m_Handle->sound		= this;
			ga_handle_play(		m_Handle);
			m_Playing			= true;
		}

		UE_void Sound::resume()
		{
			if (m_Playing)
				return;

			m_Playing		= true;
			ga_handle_play(	m_Handle);
		}

		UE_void Sound::pause()
		{
			if (!m_Playing)
				return;
			ga_handle_stop(m_Handle);
		}

		UE_void Sound::stop()
		{
			if (!m_Playing)
				return;

			ga_handle_stop(	m_Handle);
			m_Playing		= false;
		}

		UE_void Sound::setGain(UE_float gain)
		{
			if (!m_Playing)
			{
				std::cout	<< "[Sound] Cannot set gain! Sound is not currently playing!" 
							<< std::endl;
				return;
			}
			m_Gain = gain;
			ga_handle_setParamf(m_Handle, 
								GA_HANDLE_PARAM_GAIN, 
								gain);
		}

		UE_void destroy_on_finish(	ga_Handle* in_handle,
								UE_void* in_context)
		{
			Sound* sound	= (Sound*)in_handle->sound;
					sound->	m_Count--;
			if (	sound->	m_Count == 0)
				sound->stop();
		}

		UE_void loop_on_finish(ga_Handle* in_handle,
							UE_void* in_context)
		{
			Sound* sound	= (Sound*)in_handle->sound;
					sound->	loop();
			ga_handle_destroy(in_handle);
		}
	}
}