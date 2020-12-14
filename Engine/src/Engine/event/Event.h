#pragma once

#include "Engine/Core/Core.h"

namespace Engine 
{

	class Event
	{

	public:
	
		virtual ~Event() = default;

		bool handled = false;
		bool cancelled = false;
		
		template<typename EB>
		bool IsEventType()
		{
			return typeid(EB) == typeid(*this);
		}


	};

}
