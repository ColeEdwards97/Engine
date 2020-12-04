#include "engpch.h"

#include "Subject.h"

namespace Engine
{

	std::vector<Observer*> Subject::s_observers;


	void Subject::RegisterObserver(Observer* observer)
	{
		// Check to make sure this Observer isn't already registered
		if (std::find(s_observers.begin(), s_observers.end(), observer) == s_observers.end())
		{
			// Add the Observer to the vector
			s_observers.push_back(observer);
		}
	}

	void Subject::UnregisterObserver(Observer* observer)
	{
		// Check if this Observer is registered and remove it if it has
		s_observers.erase(std::remove(s_observers.begin(), s_observers.end(), observer), s_observers.end());
	}


	void Subject::Notify(Event& e)
	{
		for (std::vector<Observer*>::iterator it = s_observers.begin(); it != s_observers.end(); ++it)
		{
			(*it)->OnEvent(e);
		}
	}

}