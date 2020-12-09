#include "engpch.h"

#include "Application.h"

#include "Engine/Input.h"
#include "Engine/event/EventDispatcher.h"

#include "Engine/renderer/Renderer.h"

namespace Engine {

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		// initialize application and create window
		ENGINE_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Running = true;
		m_Window = Scope<Window>(Window::Create());
		
		// create default imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// register observer
		m_Window->RegisterObserver(this);
		
	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{

		while (m_Running)
		{
			
			// LAYER :: OnUpdate()
			for (Layer* layer : m_LayerStack)
			{
				if (layer->enabled) 
				{
					layer->OnUpdate();
				}
			}

			// LAYER :: OnImGuiRender()
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			// WINDOW :: On Update()
			m_Window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& e)
	{
		//ENGINE_CORE_TRACE("An Event Occurred!");
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ENG_BIND_EVENT_FN(Application::OnWindowClosedEvent));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
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


	bool Application::OnWindowClosedEvent(WindowCloseEvent& e)
	{
		ENGINE_CORE_TRACE("Window Close Event! goodbye!");
		m_Running = false;
		return true;
	}


	// LAYER STACK
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

}