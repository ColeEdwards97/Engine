#pragma once

#include "Engine/Layer.h"

#include "Engine/event/KeyEvent.h"
#include "Engine/event/MouseEvent.h"
#include "Engine/event/WindowEvent.h"

namespace Engine
{

	class ENGINE_API ImGuiLayer : public Layer
	{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& e);

		void blockEvents(bool block) { m_blockEvents = block; }

	private:

		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);

		bool onWindowResizeEvent(WindowResizeEvent& e);

	private:

		bool m_blockEvents = true;
		float m_time = 0.0f;

	};

}