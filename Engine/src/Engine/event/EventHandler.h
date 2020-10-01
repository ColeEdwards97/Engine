#pragma once

#include "engpch.h"

#include "Event.h"
#include "EventListener.h"

namespace Engine
{

	class ENGINE_API EventHandler
	{

	public:

		EventHandler() {};


		void addEventListener(EventType eventType, EventListener* eventListener)
		{
			// Get the vector of EventListener Pointers associated with the EventType
			std::vector<EventListener*> v = eventListeners[eventType];
			// Check to make sure this EventListener isn't already associated
			if (std::find(v.begin(), v.end(), eventListener) == v.end())
			{
				// Add the EventListener to the vector
				v.push_back(eventListener);
			}
			// Set the vector associated with the EventType
			eventListeners[eventType] = v;
		}


		void removeEventListener(EventType eventType, EventListener* eventListener)
		{
			// Check if the EventType has ever been registered
			if (eventListeners.find(eventType) != eventListeners.end())
			{
				// Get the vector of EventListener Pointers associated with the EventType
				std::vector<EventListener*> v = eventListeners[eventType];
				// Check if this EventListener is registered with the EventType and remove it if it has
				v.erase(std::remove(v.begin(), v.end(), eventListener), v.end());
				// Set the vector associated with the EventType
				eventListeners[eventType] = v;
			}

		}
		

	public:
		
		void notify(Event& e)
		{
			std::vector<EventListener*> v = eventListeners[e.getEventType()];
			for (std::vector<EventListener*>::iterator it = v.begin(); it != v.end(); ++it)
			{
				(*it)->onEvent(e);
			}
		}


		template<typename E, typename F>
		bool dispatch(Event& e, const F& func)
		{
			if (typeid(E) == typeid(e))
			{
				e.handled = func(static_cast<E&>(e));
				return true;
			}
			return false;
		}


	private:
		
		std::unordered_map<EventType, std::vector<EventListener*>> eventListeners;


	};

}