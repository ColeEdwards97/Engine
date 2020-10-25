#pragma once

#include "Event.h"
#include "Observer.h"

namespace Engine
{

	class ENGINE_API Subject
	{

	public:

		virtual ~Subject() {}

		void registerObserver(EventType eventType, Observer* observer);
		void unregisterObserver(Observer* observer);

	};

}