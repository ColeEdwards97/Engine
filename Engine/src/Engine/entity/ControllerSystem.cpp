#include "engpch.h"

#include "ControllerSystem.h"
#include "Engine/Entity/ControllerComponent.h"

namespace Engine
{

	void ControllerSystem::OnEnableImpl()
	{
		// Register the Controller Component Type
		ComponentManager::Get().RegisterComponentType<ControllerComponent>();
	}

	void ControllerSystem::OnDisableImpl()
	{

	}

	void ControllerSystem::OnUpdateImpl(TimeStep ts)
	{
		Ref<ComponentContainer<ControllerComponent>> controllers = ComponentManager::Get().GetComponents<ControllerComponent>();
		for (auto& controller : *controllers)
		{
			controller->GetController()->OnUpdate(ts);
		}
	}

	void ControllerSystem::OnEventImpl(Event& e)
	{

	}

}