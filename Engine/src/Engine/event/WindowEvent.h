#pragma once

#include "Event.h"

namespace Engine
{

	class WindowEvent : public Event
	{
	public:

		EventType getEventType() const override { return EventType::WindowEvent; }

	protected:

		WindowEvent()
		{}

	};

	class WindowResizeEvent : public WindowEvent
	{
	public:

		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height)
		{}
		
		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

	private:

		unsigned int m_width;
		unsigned int m_height;

	};

	class WindowCloseEvent : public WindowEvent
	{
	public:

		WindowCloseEvent() = default;
		
	};

}