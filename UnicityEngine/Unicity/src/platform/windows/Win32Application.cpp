#include <app/Application.h>

namespace u_engine {

	Application::Application(const UE_char* name, UE_uint width, UE_uint height)
		: m_Name(name), m_Width(width), m_Height(height) {


	}

	Application::~Application() {

		delete window;
	}

	UE_void Application::init() {

		window = new graphics::Window(m_Name, m_Width, m_Height);
	}

	UE_void Application::start() {

		init();
		m_Running = true;
		m_Suspended = false;
		run();
	}

	UE_void Application::suspend() {

		m_Suspended = true;
	}

	UE_void Application::resume() {

		m_Suspended = false;
	}

	UE_void Application::stop() {

		m_Running = false;
	}

	UE_void Application::tick() { }

	UE_void Application::update() { }
	UE_void Application::render() { }

	UE_void Application::run() {

		m_Timer = new Timer();
		UE_float timer = 0.0f;
		UE_float updateTimer = 0.0f;
		UE_float updateTick = 1.0f / 60.0f;
		UE_uint frames = 0;
		UE_uint updates = 0;
		while (m_Running) {

			window->clear();
			if (m_Timer->elapsed() - updateTimer > updateTick) {

				window->updateInput();
				update();
				updates++;
				updateTimer += updateTick;
			}
			render();
			frames++;
			window->update();
			if (m_Timer->elapsed() - timer > 1.0f) {

				timer += 1.0f;
				m_FramesPerSecond = frames;
				m_UpdatesPerSecond = updates;
				frames = 0;
				updates = 0;
				tick();
			}
			if (window->closed())
				m_Running = false;
		}
	}

}