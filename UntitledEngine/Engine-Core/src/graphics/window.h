#pragma once
#include <GLFW\glfw3.h>

namespace u_engine {
	namespace graphics {

		class Window {
		private:
			const char *m_title;
			int m_width, m_height;
			GLFWwindow* m_window;
			bool m_closed;
		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update() const;
		private:
			bool init();
		};
	}
}