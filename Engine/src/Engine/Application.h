#pragma once

#include "Core.h"
#include "Window.h"

#include "event/Event.h"
#include "event/WindowEvent.h"
#include "event/EventListener.h"

namespace Engine {

	class ENGINE_API Application : public EventListener
	{
	public:

		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e) override;
		void onWindowResizeEvent(WindowResizeEvent& e);
		void onWindowCloseEvent(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_window;
		bool m_running;

	};

	Application* createApplication();  // to be defined in CLIENT

}

