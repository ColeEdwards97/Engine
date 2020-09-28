#pragma once

#include "Engine/Input.h"

namespace Engine
{
	class WindowsInput : public Input
	{

	protected:

		virtual bool isKeyPressedImp(int keyCode) override;
		virtual bool isMouseButtonPressedImp(int button) override;
		virtual std::pair<float, float> getMousePositionImp() override;
		virtual float getMouseXImp() override;
		virtual float getMouseYImp() override;

	};
}