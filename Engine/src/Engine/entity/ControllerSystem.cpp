#include "engpch.h"

#include "ControllerSystem.h"
#include "Engine/Entity/ControllerComponent.h"

namespace Engine
{

	ControllerSystem::ControllerSystem()
		: m_Controllers(ComponentManager::Get().GetComponents<ControllerComponent>())
	{}

	void ControllerSystem::OnEnable()
	{
		
	}

	void ControllerSystem::OnDisable()
	{

	}

	void ControllerSystem::OnUpdate(TimeStep ts)
	{
		for (auto const& controller : *m_Controllers)
		{
			// only update enabled controllers
			// TODO: organize components by enabled/disabled
			if (controller->IsEnabled())
				controller->GetController().OnUpdate(ts);
		}
	}

	void ControllerSystem::OnEvent(Event& e)
	{
		for (auto const& controller : *m_Controllers)
		{
			// only update enabled controllers
			// TODO: organize components by enabled/disabled
			if (controller->IsEnabled())
				controller->GetController().OnEvent(e);
		}
	}

}