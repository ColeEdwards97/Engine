#pragma once

#include "Event.h"
#include "engpch.h"

namespace Engine
{

	class EventHandler
	{

	public:

		EventHandler(Event& e) : m_event(e) {}
		
		template<typename T, typename F>
		bool dispatchEvent(const F& func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.m_handled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}


	private:
		Event& m_event;

	};

}