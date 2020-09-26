#pragma once

#include "Engine/Window.h"
#include "Engine/Log.h"

#include <GLFW/glfw3.h>

namespace Engine {


	class ENGINE_API WindowsWindow : public Window
	{

	public:

		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		void setVSync(bool enabled) override;
		bool isVSync() const override;

	private:
		virtual void init(const WindowProperties& props);
		virtual void shutdown();

	private:

		GLFWwindow* m_window;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;
		};

		WindowData m_data;

	};

}