#pragma once

#include "Engine/Core/Window.h"
#include "Engine/Core/Log.h"

#include "Engine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Engine {


	class WindowsWindow : public Window
	{

	public:

		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		void OnEvent(Event& e) override;

		unsigned int GetWidth() const override { return m_data.width; }
		unsigned int GetHeight() const override { return m_data.height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		virtual void* GetNativeWindow() const override { return m_window; }


	private:

		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_window;
		GraphicsContext* m_context;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		WindowData m_data;

	};

}