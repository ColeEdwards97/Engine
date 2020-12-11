#pragma once

#include "Engine/Core/Input.h"

namespace Engine
{
	class WindowsInput : public Input
	{

	protected:

		virtual bool IsKeyPressedImp(int keyCode) override;
		virtual bool IsMouseButtonPressedImp(int button) override;
		virtual glm::vec2 GetMousePositionImp() override;
		virtual float GetMouseXImp() override;
		virtual float GetMouseYImp() override;

	};
}