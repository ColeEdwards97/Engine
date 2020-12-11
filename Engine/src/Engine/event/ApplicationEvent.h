#pragma once

#include "Event.h"

namespace Engine
{

	class WindowEvent : public Event
	{
	public:

		int GetEventCategoryFlags() const override { return (EventCategoryApplication); }

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
		
		unsigned int GetWidth() const { return m_width; }
		unsigned int GetHeight() const { return m_height; }

		int GetEventCategoryFlags() const override { return (EventCategoryApplication); }

	private:

		unsigned int m_width;
		unsigned int m_height;

	};

	class WindowCloseEvent : public WindowEvent
	{
	public:

		WindowCloseEvent() = default;

		int GetEventCategoryFlags() const override { return (EventCategoryApplication); }
		
	};

}