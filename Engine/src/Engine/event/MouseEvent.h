#pragma once

#include "Event.h"

namespace Engine
{

	class ENGINE_API MouseEvent : public Event
	{
	public:

		int getEventCategoryFlags() const override { return (EventCategoryMouse); }

	protected:
		
		MouseEvent()
		{}

	};


	class ENGINE_API MouseMovedEvent : public MouseEvent
	{
	public:

		MouseMovedEvent(const float posX, const float posY)
			: m_posX(posX), m_posY(posY)
		{}

		float getMouseX() const { return m_posX; }
		float getMouseY() const { return m_posY; }
		
		int getEventCategoryFlags() const override { return (EventCategoryInput | EventCategoryMouse); }

	private:

		float m_posX;
		float m_posY;

	};


	class ENGINE_API MouseScrolledEvent : public MouseEvent
	{
	public:

		MouseScrolledEvent(const float offsetX, const float offsetY)
			: m_offsetX(offsetX), m_offsetY(offsetY)
		{}

		float getOffsetX() const { return m_offsetX; }
		float getOffsetY() const { return m_offsetY; }

		int getEventCategoryFlags() const override { return (EventCategoryInput | EventCategoryMouse); }

	private:

		float m_offsetX;
		float m_offsetY;

	};


	class ENGINE_API MouseButtonEvent : public MouseEvent
	{
	public:

		int getMouseButton() const { return m_button; }

		int getEventCategoryFlags() const override { return (EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton); }

	protected:

		MouseButtonEvent(const int button)
			: m_button(button)
		{}

	private:

		int m_button;

	};

	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonPressedEvent(const int button, const uint16_t repeats)
			: MouseButtonEvent(button), m_repeats(repeats)
		{}

		uint16_t getRepeatCount() const { return m_repeats; }

	private:
		
		uint16_t m_repeats;
	
	};


	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(const int button)
			: MouseButtonEvent(button)
		{}

	};

}