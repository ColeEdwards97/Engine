#pragma once

#include "Engine/Event/Event.h"
#include "Engine/Core/Input/MouseCodes.h"

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
			: m_posX(posX), m_posY(posY)
		{}

		float GetMouseX() const { return m_posX; }
		float GetMouseY() const { return m_posY; }
		
	private:
		float m_posX;
		float m_posY;

	};


	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(const float offsetX, const float offsetY)
			: m_offsetX(offsetX), m_offsetY(offsetY)
		{}

		float GetOffsetX() const { return m_offsetX; }
		float GetOffsetY() const { return m_offsetY; }

	private:
		float m_offsetX;
		float m_offsetY;

	};


	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseCode GetMouseButton() const { return m_button; }

	protected:
		MouseButtonEvent(const MouseCode button)
			: m_button(button)
		{}

	private:
		MouseCode m_button;

	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button, const uint16_t repeats)
			: MouseButtonEvent(button), m_repeats(repeats)
		{}

		uint16_t GetRepeatCount() const { return m_repeats; }

	private:
		uint16_t m_repeats;
	
	};


	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button)
		{}

	};

}