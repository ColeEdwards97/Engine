#pragma once

#include "Event.h"

namespace Engine
{

	class ENGINE_API WindowEvent : public Event
	{
	public:

		int getEventCategoryFlags() const override { return (EventCategoryApplication); }

	protected:

		WindowEvent()
		{}

	};

	class ENGINE_API WindowResizeEvent : public WindowEvent
	{
	public:

		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height)
		{}
		
		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		int getEventCategoryFlags() const override { return (EventCategoryApplication); }

	private:

		unsigned int m_width;
		unsigned int m_height;

	};

	class ENGINE_API WindowCloseEvent : public WindowEvent
	{
	public:

		WindowCloseEvent() = default;

		int getEventCategoryFlags() const override { return (EventCategoryApplication); }
		
	};

}