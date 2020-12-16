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
			EB* e = dynamic_cast<EB*>(this);
			return (e != nullptr);
		}


	};

}
