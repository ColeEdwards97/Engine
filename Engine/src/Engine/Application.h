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

		Window& GetWindow() { return *m_window; }

		static Application& Get() { return *s_instance; }

	private:

		bool OnWindowCloseEvent(WindowCloseEvent& e);

		Scope<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running;
		LayerStack m_layerStack;

		/* hacking in triangle */
		Ref<Shader> m_shader;
		Ref<VertexArray> m_VertexArray;
		/* hacking in triangle */

	private:

		static Application* s_instance;

	};

	Application* CreateApplication();  // to be defined in CLIENT

}

