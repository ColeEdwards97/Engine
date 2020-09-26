#pragma once

#include "engpch.h"

#include "Core.h"

namespace Engine {

	struct WindowProperties {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "OpenGL Engine", 
						const unsigned int width = 1024, 
						const unsigned int height = 720) : title(title), width(width), height(height) 
		{
		}

	};

	class ENGINE_API Window {

	public:

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* create(const WindowProperties& props = WindowProperties());

	};

}