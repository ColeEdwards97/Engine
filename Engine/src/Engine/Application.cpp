#include "engpch.h"

#include "Application.h"

#include "GLFW/glfw3.h"

namespace Engine {

	Application::Application() 
	{
		m_running = true;
		m_window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application() 
	{

	}

	void Application::run() 
	{
		while (m_running)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}

}