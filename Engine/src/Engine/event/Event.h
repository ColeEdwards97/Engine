#pragma once

#include "Engine/Core.h"

namespace Engine 
{

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class Event
	{

	public:
	
		virtual ~Event() = default;

		bool handled = false;
		bool cancelled = false;

		virtual int GetEventCategoryFlags() const = 0;

		bool IsInCategory(EventCategory category)
		{
			return GetEventCategoryFlags() & category;
		}
		

	};

}
