#include "engpch.h"

#include "WindowsWindow.h"

#include "Engine/event/EventHandler.h"
#include "Engine/event/WindowEvent.h"


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