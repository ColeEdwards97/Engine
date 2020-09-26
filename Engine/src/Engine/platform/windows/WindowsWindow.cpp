#include "engpch.h"

#include "WindowsWindow.h"

namespace Engine {
	
	static bool s_isGLFWInitialized = false;

	
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


}