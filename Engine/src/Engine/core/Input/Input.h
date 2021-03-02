#pragma once

#include <glm/glm.hpp>
#include "Engine/Core/Input/KeyCodes.h"
#include "Engine/Core/Input/MouseCodes.h"

namespace Engine
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keyCode);
		static bool IsMouseButtonPressed(MouseCode mouseCode);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static const KeyCode RawToKeyCode(const int rawCode);
		static const int KeyCodeToRaw(const KeyCode keyCode);

		static const MouseCode RawToMouseCode(const int rawCode);
		static const int MouseCodeToRaw(const MouseCode mouseCode);

	};

}