#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	class Input
	{
	public:

		// Public static "Accessor" methods
		static bool IsKeyPressed(int keyCode) { return s_instance->IsKeyPressedImp(keyCode); }
		static bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImp(button); }
		static glm::vec2 GetMousePosition() { return s_instance->GetMousePositionImp(); }
		static float GetMouseX() { return s_instance->GetMouseXImp(); }
		static float GetMouseY() { return s_instance->GetMouseYImp(); }

	protected:

		// Interface methods to be overriden
		virtual bool IsKeyPressedImp(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual glm::vec2 GetMousePositionImp() = 0;
		virtual float GetMouseXImp() = 0;
		virtual float GetMouseYImp() = 0;


	private:
		// Singleton
		static Input* s_instance;

	};
}