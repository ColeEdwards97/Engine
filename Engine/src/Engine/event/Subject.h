#pragma once

#include "engpch.h"

#include "Event.h"
#include "Observer.h"

namespace Engine
{

	class ENGINE_API Subject
	{

	public:

		virtual ~Subject() {}

		void registerObserver(Observer* observer);
		void unregisterObserver(Observer* observer);

		void notify(Event& e);

	private:

		static std::vector<Observer*> s_observers;

	};

}