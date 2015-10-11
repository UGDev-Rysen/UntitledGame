#pragma once



#if WINDOWS_TIMER
	#include <Windows.h>
#else
	#include <chrono>
#endif


namespace u_engine {


#if WINDOWS_TIMER

	class Timer {


	private:
		LARGE_INTEGER m_Start;
		UE_double m_Freq;

	public:

		Timer() {

			LARGE_INTEGER frequency;	
			QueryPerformanceFrequency(&frequency);
			m_Freq = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		UE_void reset() {

			QueryPerformanceCounter(&m_Start);
		}

		UE_float elapsed() {

			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);			
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (UE_float)(cycles * m_Freq);
		}


	};

#else

		class Timer {

		private:

			typedef std::chrono::high_resolution_clock HighResClock;
			typedef std::chrono::duration<UE_float, std::milli> milliseconds_type;
			std::chrono::time_point<HighResClock> m_Start;

		public:

			Timer() {

				reset();
			}

			UE_void reset() {

				m_Start = HighResClock::now();
			}

			UE_float elapsed() {

				return std::chrono::duration_cast<milliseconds_type>(HighResClock::now() - m_Start).count() / 1000.0f;
			}

		};

#endif

}