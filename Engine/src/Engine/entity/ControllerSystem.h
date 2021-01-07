#pragma once

#include "Engine/Entity/System.h"
#include "Engine/Entity/ControllerComponent.h"

namespace Engine
{

	class ControllerSystem : public System<ControllerSystem>
	{
	public:
		ControllerSystem();
		virtual ~ControllerSystem() {}

		void OnEnable();
		void OnDisable();

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

	private:
		Ref<ComponentContainer<ControllerComponent>> m_Controllers;

	};

}