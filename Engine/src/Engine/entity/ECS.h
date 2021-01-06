#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Entity/ComponentManager.h"

namespace Engine
{

	class ECS
	{
	public:
		static ECS& Get() { return *s_Instance; }
		static void Init();

		static EntityManager& GetEntityManager() { return EntityManager::Get(); }
		static ComponentManager& GetComponentManager() { return ComponentManager::Get(); }

	private:
		static ECS* s_Instance;
	};

}