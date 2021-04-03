#include "engpch.h"

#include "WindowsWindow.h"
#include "Engine/Renderer/GraphicsContext.h"

#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

#include "Engine/Core/Input/InputConstants.h"
#include "Engine/Core/Input/InputConversion.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Engine {
	
	static bool s_isGLFWInitialized = false;

	// WINDOW IMPLEMENTATION
	Scope<Window> Window::Create(const WindowProperties& props)
	{
		return Scope<Window>(new WindowsWindow(props));
	}

	// WINDOWS WINDOW IMPLEMENTATION
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
		m_Data.width = props.width;
		m_Data.height = props.height;
		m_Data.title = props.title;
		SetEventCallback(ENG_BIND_FN(WindowsWindow::Notify));

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
		m_Window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), NULL, NULL);
		
		// OpenGL Context initialization
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		// Handle Errors
		if (m_Window == NULL) {
			ENGINE_CORE_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		else
		{
			ENGINE_CORE_INFO("Created Windows Window: {0}; {1} x {2}", props.title, props.width, props.height);
		}
		
		SetVSync(true);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		// GLFW Callbacks -----------------------

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;
				WindowResizedEvent event(width, height);
				data.eventCallback(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowClosedEvent event;
				data.eventCallback(event);
			}
		);
		
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(InputConversion::RawToKeyCode(key), false);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(InputConversion::RawToKeyCode(key));
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(InputConversion::RawToKeyCode(key), true);
					data.eventCallback(event);
					break;
				}
				default:
					break;
				}
			}
		);

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(InputConversion::RawToKeyCode(keycode));
				data.eventCallback(event);
			}
		);

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(InputConversion::RawToMouseButton(button), 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(InputConversion::RawToMouseButton(button));
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent event(InputConversion::RawToMouseButton(button), 1);
					data.eventCallback(event);
					break;
				}
				default:
					break;
				}
			}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)offsetX, (float)offsetY);
				data.eventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double posX, double posY)
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
		m_Context->SwapBuffers();
	}


	void WindowsWindow::Shutdown() 
	{
		glfwDestroyWindow(m_Window);
	}


	void WindowsWindow::SetVSync(bool enabled) 
	{
		glfwSwapInterval(enabled);
		m_Data.vSync = enabled;
	}


	bool WindowsWindow::IsVSync() const
	{
		return m_Data.vSync;
	}


	void WindowsWindow::OnEvent(Event& e)
	{
	}


}