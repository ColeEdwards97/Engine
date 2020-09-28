#include "engpch.h"

#include "WindowsWindow.h"

#include "Engine/event/EventHandler.h"
#include "Engine/event/WindowEvent.h"
#include "Engine/event/KeyEvent.h"
#include "Engine/event/MouseEvent.h"


namespace Engine {
	
	static bool s_isGLFWInitialized = false;

	// IMPLEMENTATION OF THE Window CLASS
	// (this is how the code knows to create a Windows Window and not a BlaBlaWindow)
	Window* Window::create(const WindowProperties& props) 
	{
		return new WindowsWindow(props);
	}


	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		init(props);
	}
	

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}


	void WindowsWindow::init(const WindowProperties& props) 
	{

		m_data.width = props.width;
		m_data.height = props.height;
		m_data.title = props.title;
		setEventCallback(ENG_BIND_EVENT_FN(dispatchEvent));

		// Error Callback
		glfwSetErrorCallback([](int error, const char* description)
			{
				ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			}
		);

		ENGINE_CORE_INFO("Creating Windows Window: {0}; {1} x {2}", props.title, props.width, props.height);

		if (!s_isGLFWInitialized) {
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");
			s_isGLFWInitialized = true;
		}

		//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// FOR macOS:
		//		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), NULL, NULL);
		// TODO: window create event

		if (m_window == NULL) {
			ENGINE_CORE_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		else
		{
			ENGINE_CORE_INFO("Created Windows Window: {0}; {1} x {2}", props.title, props.width, props.height);
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);


		// GLFW Callbacks -----------------------

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			}
		);

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallback(event);
			}
		);

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				default:
					break;
				}
			}
		);

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.eventCallback(event);
			}
		);

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent event(button, 1);
					data.eventCallback(event);
					break;
				}
				default:
					break;
				}
			}
		);

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double offsetX, double offsetY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)offsetX, (float)offsetY);
				data.eventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double posX, double posY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)posX, (float)posY);
				data.eventCallback(event);
			}
		);

		// --------------------------------------------

	}


	void WindowsWindow::onUpdate() 
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}


	void WindowsWindow::shutdown() 
	{
		glfwDestroyWindow(m_window);
	}


	void WindowsWindow::setVSync(bool enabled) 
	{
		glfwSwapInterval(enabled);
		m_data.vSync = enabled;
	}


	bool WindowsWindow::isVSync() const
	{
		return m_data.vSync;
	}


	void WindowsWindow::onEvent(Event& e)
	{
	}


}