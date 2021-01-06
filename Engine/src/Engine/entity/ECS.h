#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Entity/ComponentManager.h"
#include "Engine/Entity/SystemManager.h"

namespace Engine
{

	class ECS
	{
	public:
		static ECS& Get() { return *s_Instance; }
		static void Init();

		static EntityManager& GetEntityManager() { return EntityManager::Get(); }
		static ComponentManager& GetComponentManager() { return ComponentManager::Get(); }
		static SystemManager& GetSystemManager() { return SystemManager::Get(); }

	private:
		static ECS* s_Instance;
	};

}