#pragma once

#include "Core.h"

namespace Engine
{
	class Input
	{
	public:

		// Public static "Accessor" methods
		static bool isKeyPressed(int keyCode) { return s_instance->isKeyPressedImp(keyCode); }
		static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImp(button); }
		static std::pair<float, float> getMousePosition() { return s_instance->getMousePositionImp(); }
		static float getMouseX() { return s_instance->getMouseXImp(); }
		static float getMouseY() { return s_instance->getMouseYImp(); }

	protected:

		// Interface methods to be overriden
		virtual bool isKeyPressedImp(int keyCode) = 0;
		virtual bool isMouseButtonPressedImp(int button) = 0;
		virtual std::pair<float, float> getMousePositionImp() = 0;
		virtual float getMouseXImp() = 0;
		virtual float getMouseYImp() = 0;


	private:
		// Singleton
		static Input* s_instance;

	};
}