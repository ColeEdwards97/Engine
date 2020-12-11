#pragma once

#include "Core.h"
#include "Window.h"

#include "Engine/core/TimeStep.h"

#include "Engine/event/Event.h"
#include "Engine/event/ApplicationEvent.h"
#include "Engine/event/KeyEvent.h"
#include "Engine/event/MouseEvent.h"
#include "Engine/event/Observer.h"

#include "Engine/imgui/ImGuiLayer.h"
#include "Engine/LayerStack.h"

namespace Engine {

	class Application : public Observer
	{
	public:

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e) override;
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClosedEvent(WindowClosedEvent& e);
		bool OnWindowResizedEvent(WindowResizedEvent& e);

	private:

		float m_LastFrameTime = 0.0f;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

	private:

		static Application* s_Instance;

	};

	Application* CreateApplication();  // to be defined in CLIENT

}

