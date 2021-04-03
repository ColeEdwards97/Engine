#pragma once

#include "Engine/Event/Event.h"
#include "Engine/Core/Input/InputConstants.h"

namespace Engine
{

	class MouseEvent : public Event
	{
	protected:
		MouseEvent()
		{}

	};


	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(const float posX, const float posY)
			: m_PosX(posX), m_PosY(posY)
		{}

		float GetMouseX() const { return m_PosX; }
		float GetMouseY() const { return m_PosY; }
		
	private:
		float m_PosX;
		float m_PosY;

	};


	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(const float offsetX, const float offsetY)
			: m_OffsetX(offsetX), m_OffsetY(offsetY)
		{}

		float GetOffsetX() const { return m_OffsetX; }
		float GetOffsetY() const { return m_OffsetY; }

	private:
		float m_OffsetX;
		float m_OffsetY;

	};


	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButton GetMouseButton() const { return m_Button; }

	protected:
		MouseButtonEvent(const MouseButton button)
			: m_Button(button)
		{}

	private:
		MouseButton m_Button;

	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseButton button, const bool repeated)
			: MouseButtonEvent(button), m_Repeated(repeated)
		{}

		bool IsRepeated() const { return m_Repeated; }

	private:
		bool m_Repeated;
	
	};


	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseButton button)
			: MouseButtonEvent(button)
		{}

	};

}