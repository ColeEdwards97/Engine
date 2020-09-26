#pragma once

#include "Core.h"
#include "Window.h"
#include "Log.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:

		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_running;

	};

	Application* createApplication();  // to be defined in CLIENT

}

