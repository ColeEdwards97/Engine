#pragma once

#include "Event.h"

namespace Engine 
{

	class ENGINE_API EventListener
	{

	public:

		virtual ~EventListener() = default;
		virtual void onEvent(Event& e) = 0;

	};

}