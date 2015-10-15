#pragma once

#include <utils/unicitydef.h>
#include <graphics/label.h>
#include <graphics/sprite.h>
#include <graphics/renderer2d.h>
#include <graphics/batchrenderer2d.h>
#include <graphics/layers/layer.h>
#include <graphics/layers/group.h>
#include <graphics/texture_manager.h>
#include <../tilelayer.h>
#include <audio/sound.h>
#include <audio/SoundManager.h>
		 
#include <maths/maths.h>
#include <utils/timer.h>
#include <graphics/window.h>

#include <physics/Collider_2D.h>
#include <physics/PhysicsObject.h>

#include <shaders/shader.h>
#include <shaders/ShaderFactory.h>


namespace u_engine {

	class Unicity
	{
	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		UE_uint m_FramesPerSecond, m_UpdatesPerSecond;
	protected:
		Unicity()
			: m_FramesPerSecond(0), m_UpdatesPerSecond(0)
		{

		}

		virtual ~Unicity()
		{
			stop();
		}

		graphics::Window* createWindow(const UE_char *name, UE_int width, UE_int height)
		{
			m_Window = new graphics::Window(name, width, height);
			return m_Window;
		}

	public:

		UE_void start()
		{
			init();
			run();
			
		}

		UE_void stop() {
			UNICITY_FATAL("Unicity Engine is stopping...");
			delete m_Timer;
			delete m_Window;
		}

	protected:
		// Runs once upon initialization
		virtual UE_void init() = 0;
		// Runs once per second
		virtual UE_void tick() { }
		// Runs 60 times per second
		virtual UE_void update() { }
		// Runs as fast as possible (unless vsync is enabled)
		virtual UE_void render() = 0;

		const UE_uint getFPS() const { return m_FramesPerSecond; }
		const UE_uint getUPS() const { return m_UpdatesPerSecond; }
	private:
		

		UE_void run()
		{
			m_Timer = new Timer();
			UE_float timer = 0.0f;
			UE_float updateTimer = 0.0f;
			UE_float updateTick = 1.0f / 60.0f;
			UE_uint frames = 0;
			UE_uint updates = 0;
			while (!m_Window->closed())
			{
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					m_Window->updateInput();
					update();
					updates++;
					updateTimer += updateTick;
				}
				render();
				frames++;
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}
	};

}