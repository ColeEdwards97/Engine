#include "engpch.h"

#include "WindowsWindow.h"
#include "Engine/Renderer/GraphicsContext.h"

#include "Engine/Core/Input/Input.h"

#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine {
	
	static bool s_isGLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}
	

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}


	void WindowsWindow::Init(const WindowProperties& props) 
	{

		m_data.width = props.width;
		m_data.height = props.height;
		m_data.title = props.title;
		SetEventCallback(ENG_BIND_FN(Notify));

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

		// GLFWwindow creation
		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), NULL, NULL);
		
		// OpenGL Context initialization
		m_context = GraphicsContext::Create(m_window);
		m_context->Init();

		// Handle Errors
		if (m_window == NULL) {
			ENGINE_CORE_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		else
		{
			ENGINE_CORE_INFO("Created Windows Window: {0}; {1} x {2}", props.title, props.width, props.height);
		}
		
		SetVSync(false);
		glfwSetWindowUserPointer(m_window, &m_data);


		// GLFW Callbacks -----------------------

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;
				WindowResizedEvent event(width, height);
				data.eventCallback(event);
			}
		);

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowClosedEvent event;
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
					KeyPressedEvent event(Input::RawToKeyCode(key), 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(Input::RawToKeyCode(key));
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(Input::RawToKeyCode(key), 1);
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
				KeyTypedEvent event(Input::RawToKeyCode(keycode));
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
					MouseButtonPressedEvent event(Input::RawToMouseCode(button), 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(Input::RawToMouseCode(button));
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent event(Input::RawToMouseCode(button), 1);
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


	void WindowsWindow::OnUpdate() 
	{
		glfwPollEvents();
		m_context->SwapBuffers();
	}


	void WindowsWindow::Shutdown() 
	{
		glfwDestroyWindow(m_window);
	}


	void WindowsWindow::SetVSync(bool enabled) 
	{
		glfwSwapInterval(enabled);
		m_data.vSync = enabled;
	}


	bool WindowsWindow::IsVSync() const
	{
		return m_data.vSync;
	}


	void WindowsWindow::OnEvent(Event& e)
	{
	}


}