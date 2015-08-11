#include "window.h"
#include <GLFW\glfw3.h>
#include <iostream>



namespace u_engine { namespace graphics {

	void windowResize(GLFWwindow *window, int width, int height);
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
			glfwSetWindowSizeCallback(m_window, windowResize);
			return true;

		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_window) == 1;
		}


		void windowResize(GLFWwindow *window, int width, int height) {
//			glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glViewport(0, 0, width, height);
		}
} }
