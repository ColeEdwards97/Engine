#pragma once

#include "Entity.h"

namespace Engine
{
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void OnUpdate(Entity& entity) = 0;
	};
}