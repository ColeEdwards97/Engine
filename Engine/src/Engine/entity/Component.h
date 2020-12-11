#pragma once

#include "Engine/Entity/Entity.h"

namespace Engine
{
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void OnUpdate(Entity& entity) = 0;
	};
}