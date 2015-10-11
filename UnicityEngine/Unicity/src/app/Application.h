#include <u_engine_includes.h>

#include <graphics/window.h>
#include <utils/timer.h>

namespace u_engine {

	class Application {

	public:
		graphics::Window* window;

	private:
		UE_bool m_Running, m_Suspended;
		Timer* m_Timer;
		UE_uint m_UpdatesPerSecond, m_FramesPerSecond;

		const UE_char* m_Name;
		UE_uint m_Width, m_Height;

	public:
		Application(const UE_char* name, UE_uint width, UE_uint height);
		virtual ~Application();

		virtual UE_void init();

		UE_void start();
		UE_void suspend();
		UE_void resume();
		UE_void stop();

		virtual UE_void tick();
		virtual UE_void update();
		virtual UE_void render();

		const UE_int getFPS() const { return m_FramesPerSecond; }
		const UE_int getUPS() const { return m_UpdatesPerSecond; }

	private:
		UE_void run();

	};
}