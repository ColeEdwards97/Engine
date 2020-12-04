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
		m_window = std::unique_ptr<Window>(Window::Create());
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// REGISTER OBSERVER
		m_window->RegisterObserver(this);
	}

	Application::~Application() 
	{

	}

	void Application::Run() 
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
					layer->OnUpdate();
				}
			}

			// LAYER :: OnImGuiRender()
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			// WINDOW :: On Update()
			m_window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& e)
	{
		//ENGINE_CORE_TRACE("An Event Occurred!");
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ENG_BIND_EVENT_FN(Application::OnWindowCloseEvent));

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (e.handled) 
			{
				break;
			}
			else
			{
				(*it)->OnEvent(e);
			}
		}

	}


	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		ENGINE_CORE_TRACE("Window Close Event! goodbye!");
		m_running = false;
		return true;
	}


	// LAYER STACK
	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

}