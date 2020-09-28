#pragma once

#include "Core.h"
#include "Window.h"

#include "event/Event.h"
#include "event/WindowEvent.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/EventListener.h"

#include "LayerStack.h"

namespace Engine {

	class ENGINE_API Application : public EventListener
	{
	public:

		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e) override;
		bool onWindowResizeEvent(WindowResizeEvent& e);
		bool onWindowCloseEvent(WindowCloseEvent& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		Window& getWindow() { return *m_window; }

		static Application& get() { return *s_instance; }

	private:

		static Application* s_instance;

		std::unique_ptr<Window> m_window;
		bool m_running;

		LayerStack m_layerStack;

	};

	Application* createApplication();  // to be defined in CLIENT

}

