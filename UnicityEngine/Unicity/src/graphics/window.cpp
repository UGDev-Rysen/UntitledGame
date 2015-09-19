#include "window.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>



namespace u_engine { namespace graphics {

	void window_resize(GLFWwindow *window, int width, int height);

	Window::Window(const char *title, int width, int height) {
			m_title = title;
			m_width = width;
			m_height = height;
			if (!init()) 
				glfwTerminate();



			for (int i = 0; i < MAX_KEYS; i++) {
				m_keys[i] = false;
			}	
			
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_mousebuttons[i] = false;
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
				std::cout << "GLFW Window initialized successfully!" << std::endl;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, window_resize);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);
			glfwSwapInterval(0.0);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			} else {
				std::cout << "GLEW initialized successfully!" << std::endl;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const {
			//TODO: Log this!
			if (keycode >= MAX_KEYS) {
				return false;

			}
			return m_keys[keycode];
		}

		bool Window::isMButtonPressed(unsigned int button) const {
			//TODO: Log this!
			if (button >= MAX_BUTTONS) {
				return false;

			}
			return m_mousebuttons[button];
		}

		void Window::getMousePosition(double& x, double& y) const {
			x = m_mx;
			y = m_my;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_window) == 1;
		}


		void window_resize(GLFWwindow *window, int width, int height) {
//			glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glViewport(0, 0, width, height);
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_mousebuttons[button] = action != GLFW_RELEASE;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_keys[key] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_mx = xpos;
			win->m_my = ypos;
		}



} }
