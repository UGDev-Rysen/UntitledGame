#include <graphics/window.h>
#include <embedded/Embedded.h>

namespace u_engine { namespace graphics {

#ifndef UNICITY_USE_NATIVE_WINDOW

	UE_void window_resize(GLFWwindow* window, UE_int width, UE_int height);
	UE_void key_callback(GLFWwindow* window, UE_int key, UE_int scancode, UE_int action, UE_int mods);
	UE_void mouse_button_callback(GLFWwindow* window, UE_int button, UE_int action, UE_int mods);
	UE_void cursor_position_callback(GLFWwindow* window, UE_double xpos, UE_double ypos);

	Window::Window(const UE_char *title, UE_int width, UE_int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();


		FontManager::add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));




		audio::SoundManager::init();

		for (UE_int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}

		for (UE_int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
	}

	Window::~Window()
	{
		FontManager::clean();
		TextureManager::clean();
		audio::SoundManager::clean();
		glfwTerminate();
	}

	UE_bool Window::init()
	{
		if (!glfwInit())
		{
			UNICITY_FATAL("Failed to initialize GLFW!");
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			UNICITY_FATAL("Failed to create GLFW window!");
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		

		if (glewInit() != GLEW_OK)
		{
			UNICITY_FATAL("Could not initialize GLEW!");
			return false;
		}


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		UNICITY_WARN("OpenGL ", glGetString(GL_VERSION));
		return true;
	}

	UE_bool Window::isKeyPressed(UE_uint keycode) const
	{
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}

	UE_bool Window::isKeyTyped(UE_uint keycode) const
	{
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_KeyTyped[keycode];
	}
	 
	UE_bool Window::isMouseButtonPressed(UE_uint button) const
	{
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	UE_bool Window::isMouseButtonClicked(UE_uint button) const
	{
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseClicked[button];
	}

	const maths::vec2& Window::getMousePosition() const
	{
		return m_MousePosition;
	}

	UE_void Window::setVsync(bool enabled) {

		glfwSwapInterval((UE_double)enabled);
		m_Vsync = enabled;
	}

	UE_void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

 	UE_void Window::update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		audio::SoundManager::update();
	}

	UE_void Window::updateInput()
	{
		for (UE_int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (UE_int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
	}

	UE_bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	UE_void window_resize(GLFWwindow *window, UE_int width, UE_int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	UE_void key_callback(GLFWwindow* window, UE_int key, UE_int scancode, UE_int action, UE_int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	UE_void mouse_button_callback(GLFWwindow* window, UE_int button, UE_int action, UE_int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	UE_void cursor_position_callback(GLFWwindow* window, UE_double xpos, UE_double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MousePosition.x = (UE_float) xpos;
		win->m_MousePosition.y = (UE_float) ypos;
	}

	#else

	std::map<void*, Window*> Window::s_Handles;

	Window::Window(const char *title, UE_uint width, UE_uint height)
		: m_Title(title), m_Width(width), m_Height(height), m_Handle(nullptr), m_Closed(false)
	{
		if (!init())
		{
			UNICITY_ERROR("Failed base Window initialization!");
			return;
		}


		FontManager::add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));


		audio::SoundManager::init();

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
			m_KeyState[i] = false;
			m_KeyTyped[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
		m_MouseGrabbed = true;
	}

	Window::~Window()
	{
		FontManager::clean();
		TextureManager::clean();
		audio::SoundManager::clean();
	}

	bool Window::init()
	{
		if (!platformInit())
		{
			UNICITY_FATAL("Failed to initialize platform!");
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		UNICITY_INFO("-------------------------------------------------------------------");
		UNICITY_INFO(" OpenGL:                                                           ");
		UNICITY_INFO("    ", glGetString(GL_VERSION));
		UNICITY_INFO("    ", glGetString(GL_VENDOR));
		UNICITY_INFO("    ", glGetString(GL_RENDERER));
		UNICITY_INFO("-------------------------------------------------------------------");
		return true;
	}

	bool Window::isKeyPressed(UE_uint keycode) const
	{
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}

	bool Window::isKeyTyped(UE_uint keycode) const
	{
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_KeyTyped[keycode];
	}

	bool Window::isMouseButtonPressed(UE_uint button) const
	{
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	bool Window::isMouseButtonClicked(UE_uint button) const
	{
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseClicked[button];
	}

	const maths::vec2& Window::getMousePosition() const
	{
		return m_MousePosition;
	}

	const UE_bool Window::isMouseGrabbed() const {

		return m_MouseGrabbed;
	}

	UE_void Window::setMouseGrabbed(bool grabbed) {

		m_MouseGrabbed = grabbed;
	}

	void Window::setVsync(bool enabled)
	{
		// TODO: Not implemented
		m_Vsync = enabled;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		platformUpdate();
		audio::SoundManager::update();
	}

	void Window::updateInput()
	{
		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
	}

	bool Window::closed() const
	{
		return m_Closed;
	}

	void Window::RegisterWindowClass(void* handle, Window* window)
	{
		s_Handles[handle] = window;
	}

	Window* Window::GetWindowClass(void* handle)
	{
		return s_Handles[handle];
	}
#endif

} }