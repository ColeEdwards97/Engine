#pragma once

#include "engpch.h"

#include "Event.h"

namespace Engine
{

	class EventDispatcher
	{

	public:

		EventDispatcher(Event& e)
			: m_event(e)
		{}


		template<typename E, typename F>
		bool dispatch(const F& func)
		{
			if (typeid(E) == typeid(m_event))
			{
				m_event.handled = func(static_cast<E&>(m_event));
				return true;
			}
			return false;
		}


	private:

		Event& m_event;


	};

}