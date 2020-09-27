#include "engpch.h"

#include "Application.h"

#include "GLFW/glfw3.h"

namespace Engine {

	Application::Application() 
	{
		m_running = true;
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->addEventListener(EventType::WindowEvent, this);
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

	void Application::onEvent(Event& e)
	{
		ENGINE_CORE_INFO("An event occurred!");
		
		m_window->forwardEvent<WindowResizeEvent>(e, ENG_BIND_EVENT_FN(Application::onWindowResizeEvent));
		m_window->forwardEvent<WindowCloseEvent>(e, ENG_BIND_EVENT_FN(Application::onWindowCloseEvent));
	}

	void Application::onWindowResizeEvent(WindowResizeEvent& e)
	{
		ENGINE_CORE_INFO("Window Resize Event! new size: {0} x {1}", e.getWidth(), e.getHeight());
	}

	void Application::onWindowCloseEvent(WindowCloseEvent& e)
	{
		ENGINE_CORE_INFO("Window Close Event! goodbye!");
		m_running = false;
	}

}