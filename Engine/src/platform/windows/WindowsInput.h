#pragma once

#include "Engine/Input.h"

namespace Engine
{
	class WindowsInput : public Input
	{

	protected:

		virtual bool IsKeyPressedImp(int keyCode) override;
		virtual bool IsMouseButtonPressedImp(int button) override;
		virtual std::pair<float, float> GetMousePositionImp() override;
		virtual float GetMouseXImp() override;
		virtual float GetMouseYImp() override;

	};
}