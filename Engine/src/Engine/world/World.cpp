#include "engpch.h"

#include "World.h"

namespace Engine
{

	[[nodiscard]] EntityID World::CreateEntity() {
		return m_Registry.Create();
	}

}