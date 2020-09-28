#pragma once

#include "engpch.h"

namespace Engine 
{

	enum EventType
	{
		None = 0,
		WindowEvent,
		KeyboardEvent,
		MouseEvent
	};

	class ENGINE_API Event
	{

	public:

		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		
		bool handled = false;

	};

}
