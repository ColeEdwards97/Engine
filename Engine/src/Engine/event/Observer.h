#pragma once

#include "Engine/Core.h"
#include "Event.h"

namespace Engine
{

	class Observer
	{

	public:

		virtual ~Observer() = default;
		virtual void onEvent(Event& e) = 0;

	};

}
