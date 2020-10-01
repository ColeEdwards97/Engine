#include "engpch.h"

#include "Application.h"

#include "GLFW/glfw3.h"

#include "Input.h"

namespace Engine {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		m_running = true;
		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::create());

		// REGISTER EVENT LISTENERS
		m_window->addEventListener(EventType::WindowEvent, this);
		m_window->addEventListener(EventType::MouseEvent, this);
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

			for (Layer* layer : m_layerStack)
			{
				if (layer->enabled) 
				{
					layer->onUpdate();
				}
			}

			m_window->onUpdate();

		}
	}

	void Application::onEvent(Event& e)
	{
		ENGINE_CORE_TRACE("An Event Occurred!");
		
		m_window->dispatch<WindowResizeEvent>(e, ENG_BIND_EVENT_FN(Application::onWindowResizeEvent));
		m_window->dispatch<WindowCloseEvent>(e, ENG_BIND_EVENT_FN(Application::onWindowCloseEvent));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (e.handled) 
			{
				break;
			}
			(*it)->onEvent(e);
		}

	}

	bool Application::onWindowResizeEvent(WindowResizeEvent& e)
	{
		ENGINE_CORE_TRACE("Window Resize Event! new size: {0} x {1}", e.getWidth(), e.getHeight());
		return false;
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& e)
	{
		ENGINE_CORE_TRACE("Window Close Event! goodbye!");
		m_running = false;
		return true;
	}


	// LAYER STACK
	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
	}

}