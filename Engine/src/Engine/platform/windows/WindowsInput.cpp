#include "engpch.h"

#include "WindowsInput.h"

#include "Engine/Application.h"

#include "GLFW/glfw3.h"

namespace Engine
{
	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImp(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool WindowsInput::isMouseButtonPressedImp(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	std::pair<float, float> WindowsInput::getMousePositionImp()
	{
		double xpos;
		double ypos;
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::make_pair((float)xpos, (float)ypos);
	}

	float WindowsInput::getMouseXImp()
	{
		return getMousePositionImp().first;
	}

	float WindowsInput::getMouseYImp()
	{
		return getMousePositionImp().second;
	}


}