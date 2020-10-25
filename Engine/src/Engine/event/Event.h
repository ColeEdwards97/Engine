#pragma once

#include "engpch.h"

namespace Engine 
{

	enum EventType
	{
		None = 0,
		WindowResize, WindowClose,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory
	{
		//None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class ENGINE_API Event
	{

	public:

		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		virtual int getEventCategoryFlags() const = 0;

		bool isInCategory(EventCategory category) { return (getEventCategoryFlags() & category); }
		
		bool handled = false;

	};

}
