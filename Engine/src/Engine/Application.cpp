#include "engpch.h"

#include "Application.h"

#include "glad/glad.h"

#include "Input.h"

#include "event/EventDispatcher.h"

namespace Engine {

	Application* Application::s_instance = nullptr;

	Application::Application() 
	{
		ENGINE_CORE_ASSERT(!s_instance, "Application already exists");
		s_instance = this;
		m_running = true;
		m_window = std::unique_ptr<Window>(Window::create());
		
		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		// REGISTER OBSERVER
		m_window->registerObserver(this);
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

			// LAYER :: OnUpdate()
			for (Layer* layer : m_layerStack)
			{
				if (layer->enabled) 
				{
					layer->onUpdate();
				}
			}

			// LAYER :: OnImGuiRender()
			m_ImGuiLayer->begin();
			for (Layer* layer : m_layerStack)
			{
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();


			// WINDOW :: On Update()
			m_window->onUpdate();

		}
	}

	void Application::onEvent(Event& e)
	{
		//ENGINE_CORE_TRACE("An Event Occurred!");
		
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(ENG_BIND_EVENT_FN(Application::onWindowCloseEvent));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (e.handled) 
			{
				break;
			}
			else
			{
				(*it)->onEvent(e);
			}
		}

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
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

}