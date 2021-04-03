#include "engpch.h"

#include "Engine/Core/Input/Input.h"
#include "Engine/Core/Input/InputConversion.h"
#include "Engine/Core/Application.h"
#include "Platform/Windows/WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace Engine
{

	// INPUT IMPLEMENTATION
	Scope<Input> Input::Create()
	{
		return Scope<Input>(new Input());
	}

	// WINDOWS INPUT IMPLEMENTATION
	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, InputConversion::KeyCodeToRaw(key));
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool Input::IsKeyReleased(const KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, InputConversion::KeyCodeToRaw(key));
		return (state == GLFW_RELEASE);
	}

	bool Input::IsMouseButtonPressed(const MouseButton button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, InputConversion::MouseButtonToRaw(button));
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool Input::IsMouseButtonReleased(const MouseButton button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, InputConversion::MouseButtonToRaw(button));
		return (state == GLFW_RELEASE);
	}

	glm::vec2 Input::GetMousePosition()
	{
		double xpos;
		double ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return glm::vec2((float)xpos, (float)ypos);
	}
	float Input::GetMouseX() {
		return GetMousePosition().x;
	}
	float Input::GetMouseY() {
		return GetMousePosition().y;
	}

}