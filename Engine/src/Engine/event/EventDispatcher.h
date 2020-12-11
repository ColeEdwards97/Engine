#pragma once

#include "Engine/Event/Event.h"

namespace Engine
{

	class EventDispatcher
	{

	public:

		EventDispatcher(Event& e)
			: m_event(e)
		{}


		template<typename E, typename F>
		bool Dispatch(const F& func)
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