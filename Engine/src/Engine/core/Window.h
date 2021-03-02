#pragma once

#include "Engine/Event/Event.h"

namespace Engine {

	struct WindowProperties {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "OpenGL Engine", 
						const unsigned int width = 1024, 
						const unsigned int height = 720) : title(title), width(width), height(height) 
		{}

	};

	class Window : public Subject {

	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		
		virtual void* GetNativeWindow() const = 0;
		
		static Window* Create(const WindowProperties& props = WindowProperties());

	};

}