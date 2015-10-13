#pragma once

#include <iostream>
#include <string>
#include <u_engine_includes.h>
#include <utils/unicitydef.h>
#include <gorilla-audio/ga.h>
#include <gorilla-audio/gau.h>

namespace u_engine { namespace audio {

		class Sound
		{
		private:
			UE_string			m_Name;
			UE_string			m_Filename;
			UE_uint				m_Count;
			ga_Sound*			m_Sound;
			ga_Handle*			m_Handle;
			gc_int32			m_Position;

			UE_bool				m_Playing;
			UE_float				m_Gain;
		public:
			Sound(	const UE_string& name,
					const UE_string& filename);
			~Sound();


			UE_void play();
			UE_void loop();
			UE_void pause();
			UE_void resume();
			UE_void stop();

			UE_void setGain(UE_float gain);

			inline const UE_bool				isPlaying()		const { return m_Playing; }
			inline const UE_float				getGain()		const { return m_Gain; }
			inline const UE_string&		getName()		const { return m_Name; }
			inline const UE_string&		getFileName()	const { return m_Filename; }

			friend UE_void	destroy_on_finish(	ga_Handle* in_handle, UE_void* in_context);
			friend UE_void loop_on_finish(		ga_Handle* in_handle, UE_void* in_context);

		};

	}
}