#include "window.h"
#include <GLFW\glfw3.h>
#include <iostream>
namespace u_engine {
	namespace graphics {
		Window::Window(const char *title, int width, int height) {
			m_title = title;
			m_width = width;
			m_height = height;
			if (!init()) {
				glfwTerminate();
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Error: Failed to initialize GLFW!" << std::endl;
				return false;
			}
			else {
				std::cout << "GLFW initialized successfully!" << std::endl;
				
			}
			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window) {
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			else {
				std::cout << "GLFW Window initiated successfully!" << std::endl;				
			}
			glfwMakeContextCurrent(m_window);
			return true;

		}
		bool Window::closed() const {
			return glfwWindowShouldClose(m_window);
		}


		void Window::update() const {
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}
	}
}