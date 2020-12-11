#pragma once

#include "Engine/Event/Event.h"

namespace Engine
{

	class Observer
	{

	public:

		virtual ~Observer() = default;
		virtual void OnEvent(Event& e) = 0;

	};

}
