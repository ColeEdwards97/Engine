#include "engpch.h"

#include "WindowsInput.h"

#include "Engine/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Engine
{
	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImp(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool WindowsInput::IsMouseButtonPressedImp(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	glm::vec2 WindowsInput::GetMousePositionImp()
	{
		double xpos;
		double ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return glm::vec2((float)xpos, (float)ypos);
	}

	float WindowsInput::GetMouseXImp()
	{
		return GetMousePositionImp().x;
	}

	float WindowsInput::GetMouseYImp()
	{
		return GetMousePositionImp().y;
	}


}