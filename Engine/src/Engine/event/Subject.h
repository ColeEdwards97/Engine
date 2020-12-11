#pragma once

#include "engpch.h"

#include "Engine/Event/Event.h"
#include "Engine/Event/Observer.h"

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