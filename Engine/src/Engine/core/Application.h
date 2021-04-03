#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Window.h"

#include "Engine/Core/Input/Input.h"

#include "Engine/Core/TimeStep.h"

#include "Engine/Event/Event.h"
#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Core/LayerStack.h"

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
		Input& GetInput() { return *m_Input; }

		static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClosedEvent(WindowClosedEvent& e);
		bool OnWindowResizedEvent(WindowResizedEvent& e);

	private:

		float m_LastFrameTime = 0.0f;
		Scope<Window> m_Window;
		Scope<Input> m_Input;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

	private:

		static Application* s_Instance;

	};

	Application* CreateApplication();  // to be defined in CLIENT

}

