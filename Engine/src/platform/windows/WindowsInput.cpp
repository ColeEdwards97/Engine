#include "engpch.h"

#include "Engine/Core/Input/Input.h"

#include "Engine/Core/Application.h"

#include "Platform/Windows/WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace Engine
{

	bool Input::IsKeyPressed(KeyCode keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, KeyCodeToRaw(keyCode));
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, MouseCodeToRaw(button));
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	glm::vec2 Input::GetMousePosition()
	{
		double xpos;
		double ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return glm::vec2((float)xpos, (float)ypos);
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}



	const KeyCode Input::RawToKeyCode(const int rawCode) {
		return static_cast<KeyCode>(rawCode);
	}

	const int Input::KeyCodeToRaw(const KeyCode keyCode) {
		return static_cast<int>(keyCode);
	}

	const MouseCode Input::RawToMouseCode(const int rawCode) {
		return static_cast<MouseCode>(rawCode);
	}

	const int Input::MouseCodeToRaw(const MouseCode mouseCode) {
		return static_cast<int>(mouseCode);
	}


}