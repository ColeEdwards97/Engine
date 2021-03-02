#include "engpch.h"

#include "Application.h"
#include "Engine/Core/Platform.h"
#include "Engine/Renderer/Renderer.h"

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

		// register events
		// general interest in events from m_Window
		m_Window->RegisterObserver(this);
				
	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{

		while (m_Running)
		{

			// Time Calculation
			float time = Platform::GetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// only call on update if we're not minimized
			
			if (!m_Minimized)
			{

				// LAYER :: OnUpdate()
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timeStep);
				}

			}

			// still update imgui though

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
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(ENG_BIND_FN(Application::OnWindowClosedEvent));
		dispatcher.Dispatch<WindowResizedEvent>(ENG_BIND_FN(Application::OnWindowResizedEvent));

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


	/* EVENT CALLBACKS */

	bool Application::OnWindowClosedEvent(WindowClosedEvent& e)
	{
		ENGINE_CORE_TRACE("Window Close Event! goodbye!");
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResizedEvent(WindowResizedEvent& e)
	{

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		
		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());

		return false;
	}

	/* LAYER STACK */

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

}