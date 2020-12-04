#pragma once

#include "engpch.h"

#include "Core.h"

#include "event/Subject.h"

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

		using eventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const eventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;


		virtual void* getNativeWindow() const = 0;


		static Window* create(const WindowProperties& props = WindowProperties());

		virtual void onEvent(Event& e) = 0;

	};

}