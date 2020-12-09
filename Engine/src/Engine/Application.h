#pragma once

#include "Core.h"
#include "Window.h"

#include "Engine/event/Event.h"
#include "Engine/event/WindowEvent.h"
#include "Engine/event/KeyEvent.h"
#include "Engine/event/MouseEvent.h"
#include "Engine/event/Observer.h"

#include "Engine/imgui/ImGuiLayer.h"
#include "Engine/LayerStack.h"

/* HACKING IN A TRIANGLE */
#include "Engine/renderer/Shader.h"
#include "Engine/renderer/Buffer.h"
#include "Engine/renderer/VertexArray.h"
#include "Engine/renderer/OrthographicCamera.h"
#include "Engine/renderer/PerspectiveCamera.h"
/* HACKING IN A TRIANGLE */


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

		bool OnWindowCloseEvent(WindowCloseEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		/* hacking in triangle */
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;

		PerspectiveCamera m_Camera;
		//OrthographicCamera m_Camera;
		/* hacking in triangle */

	private:

		static Application* s_Instance;

	};

	Application* CreateApplication();  // to be defined in CLIENT

}

