#pragma once

#include "Engine/Core/TimeStep.h"
#include "Engine/Entity/IEntity.h"

namespace Engine
{

	class IController
	{
	public:
		IController()
		{}

		virtual ~IController()
		{}

		virtual void OnUpdate(TimeStep ts) = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void Possess(EntityID id) = 0;
		virtual void Possess(Ref<IEntity> e) = 0;
		virtual void Unpossess() = 0;

	};

}