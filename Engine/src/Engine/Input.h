#pragma once

#include "Core.h"

namespace Engine
{
	class ENGINE_API Input
	{
	public:

		// Public static "Accessor" methods
		inline static bool isKeyPressed(int keyCode) { return s_instance->isKeyPressedImp(keyCode); }
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImp(button); }
		inline static std::pair<float, float> getMousePosition() { return s_instance->getMousePositionImp(); }
		inline static float getMouseX() { return s_instance->getMouseXImp(); }
		inline static float getMouseY() { return s_instance->getMouseYImp(); }

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