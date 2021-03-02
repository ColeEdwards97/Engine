#include "engpch.h"

#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Engine
{
	Window* Window::Create(const WindowProperties& props)
	{
		// TODO: platform detection
		return new WindowsWindow(props);
	}
}