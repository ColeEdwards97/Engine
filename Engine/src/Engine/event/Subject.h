#pragma once

#include "engpch.h"

#include "Event.h"
#include "Observer.h"

namespace Engine
{

	class Subject
	{

	public:

		virtual ~Subject() {}

		void RegisterObserver(Observer* observer);
		void UnregisterObserver(Observer* observer);

		void Notify(Event& e);

	private:

		static std::vector<Observer*> s_observers;

	};

}