#pragma once

#include "Event.h"

namespace Engine
{

	class WindowResizeEvent : public Event
	{
	public:

		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height)
		{}

		EventType getEventType() const override { return EventType::WindowEvent; }

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }


	private:

		unsigned int m_width;
		unsigned int m_height;

	};

	class WindowCloseEvent : public Event
	{
	public:

		WindowCloseEvent() = default;

		EventType getEventType() const override { return EventType::WindowEvent; }

	};

}