#pragma once

#include "Entity.h"

namespace Engine
{
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void onUpdate(Entity& entity) = 0;
	};
}