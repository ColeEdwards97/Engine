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

namespace Engine {

	class ENGINE_API Application : public Observer
	{
	public:

		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e) override;
		
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		Window& getWindow() { return *m_window; }

		static Application& get() { return *s_instance; }

	private:

		bool onWindowCloseEvent(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running;
		LayerStack m_layerStack;

	private:

		static Application* s_instance;

	};

	Application* createApplication();  // to be defined in CLIENT

}

