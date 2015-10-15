#pragma once

#include <iostream>



#include <u_engine_includes.h>
#include <utils/unicitydef.h>

#include <maths/vec2.h>
#include <graphics/font_manager.h>
#include <graphics/texture_manager.h>
#include <audio/SoundManager.h>


namespace u_engine { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

#ifndef UNICITY_USE_NATIVE_WINDOW

		class Window
		{
		private:
			const UE_char *m_Title;
			UE_int m_Width, m_Height;
			GLFWwindow *m_Window;
			UE_bool m_Closed;



			UE_bool m_Keys[MAX_KEYS];
			UE_bool m_KeyState[MAX_KEYS];
			UE_bool m_KeyTyped[MAX_KEYS];
			UE_bool m_MouseButtons[MAX_BUTTONS];
			UE_bool m_MouseState[MAX_BUTTONS];
			UE_bool m_MouseClicked[MAX_BUTTONS];

			maths::vec2 m_MousePosition;

			UE_bool m_Vsync;

		public:
			Window(const UE_char *name, UE_int width, UE_int height);
			~Window();
			UE_void clear() const;
			UE_void update();
			UE_void updateInput();
			UE_bool closed() const;

			inline UE_int getWidth() const { return m_Width; }
			inline UE_int getHeight() const { return m_Height; }

			UE_bool isKeyPressed(UE_uint keycode) const;
			UE_bool isKeyTyped(UE_uint keycode) const;
			UE_bool isMouseButtonPressed(UE_uint button) const;
			UE_bool isMouseButtonClicked(UE_uint button) const;
			const maths::vec2& getMousePosition() const;

			UE_void setVsync(bool enabled);
			UE_bool isVsync() const { return m_Vsync; }

		private:
			UE_bool init();
			friend UE_void window_resize(GLFWwindow* window, UE_int width, UE_int height);
			friend UE_void key_callback(GLFWwindow* window, UE_int key, UE_int scancode, UE_int action, UE_int mods);
			friend UE_void mouse_button_callback(GLFWwindow* window, UE_int button, UE_int action, UE_int mods);
			friend UE_void cursor_position_callback(GLFWwindow* window, UE_double xpos, UE_double ypos);
		};

#else

	class Window
		{
		private:
			static std::map<void*, Window*> s_Handles;
		private:
			const char *m_Title;
			int m_Width, m_Height;
			bool m_Closed;
			void* m_Handle;
	
			bool m_Keys[MAX_KEYS];
			bool m_KeyState[MAX_KEYS];
			bool m_KeyTyped[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			bool m_MouseState[MAX_BUTTONS];
			bool m_MouseClicked[MAX_BUTTONS];
			bool m_MouseGrabbed;
	
			maths::vec2 m_MousePosition;
			bool m_Vsync;
		public:
			Window(const char *name, UE_uint width, UE_uint height);
			~Window();
			void clear() const;
			void update();
			void updateInput();
			bool closed() const;
	
			inline UE_uint getWidth() const { return m_Width; }
			inline UE_uint getHeight() const { return m_Height; }
	
			bool isKeyPressed(UE_uint keycode) const;
			bool isKeyTyped(UE_uint keycode) const;
			bool isMouseButtonPressed(UE_uint button) const;
			bool isMouseButtonClicked(UE_uint button) const;
			
			const maths::vec2& getMousePosition() const;
			UE_void	setMousePosition(const maths::vec2& position);
			const UE_bool isMouseGrabbed() const;
			void setMouseGrabbed(bool grabbed);
			UE_void setMouseCursor(int cursor);


			void setVsync(bool enabled);
			bool ssVsync() const { return m_Vsync; }
		private:
			bool init();
			
			bool platformInit();
			void platformUpdate();
	
			friend void resize_callback(Window* window, int width, int height);
			friend void key_callback(Window* window, int key, UE_uint message);
			friend void mouse_button_callback(Window* window, int button, int x, int y);
		public:
			static void RegisterWindowClass(void* handle, Window* window);
			static Window* GetWindowClass(void* handle);
		};
#endif
} }