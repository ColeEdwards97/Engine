#pragma once

#include "Engine/Core.h"
#include "Event.h"

namespace Engine
{

	class Observer
	{

	public:

		virtual ~Observer() = default;
		virtual void OnEvent(Event& e) = 0;

	};

}
